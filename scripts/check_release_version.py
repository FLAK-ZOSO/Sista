#!/usr/bin/env python3
"""Check that a release tag and every package's version agree."""

import re
import sys
from pathlib import Path


def main() -> int:
    if len(sys.argv) != 2:
        print("usage: check_release_version.py vMAJOR.MINOR.PATCH[rcN]", file=sys.stderr)
        return 2

    match = re.fullmatch(r"v(?P<base>\d+\.\d+\.\d+)(?:rc(?P<rc>\d+))?", sys.argv[1])
    if match is None:
        print(f"Unsupported release tag: {sys.argv[1]}", file=sys.stderr)
        return 1

    version = sys.argv[1][1:]
    base = match.group("base")
    rc = match.group("rc")
    debian_version = f"{base}~rc{rc}" if rc is not None else base
    rpm_release = f"0.rc{rc}" if rc is not None else "1"

    checks = {
        "include/sista/version.hpp": f'#define SISTA_VERSION "{version}"',
        "python/src/sista/__init__.py": f"__version__ = '{version}'",
        "python/src/sista/__init__.pyi": f"__version__ = '{version}'",
        "Doxyfile": f"PROJECT_NUMBER         = v{version}",
        "packageroot/rpm/sista.spec": f"Version:        %{{?sista_version}}%{{!?sista_version:{base}}}",
        "ReleaseNotes.md": f"## v`{version}`",
    }
    errors = []
    for name, expected in checks.items():
        lines = Path(name).read_text().splitlines()
        if expected not in lines:
            errors.append(f"{name}: expected {expected}")

    header_lines = Path("include/sista/version.hpp").read_text().splitlines()
    for part, number in zip(("MAJOR", "MINOR", "PATCH"), base.split(".")):
        expected = f"#define SISTA_VERSION_{part} {number}"
        if expected not in header_lines:
            errors.append(f"include/sista/version.hpp: expected {expected}")

    debian_first_line = Path("packageroot/debian/changelog").read_text().splitlines()[0]
    expected_debian = f"sista ({debian_version}) unstable; urgency=medium"
    if debian_first_line != expected_debian:
        errors.append(f"packageroot/debian/changelog: expected {expected_debian}")

    changelog_first_version = next(
        (line for line in Path("changelog.md").read_text().splitlines()
         if line.startswith("## [") and line != "## [Unreleased]"),
        None,
    )
    if not changelog_first_version or not re.fullmatch(
        rf"## \[{re.escape(version)}\] - \d{{4}}-\d{{2}}-\d{{2}}", changelog_first_version
    ):
        errors.append(f"changelog.md: expected first version heading for {version}")

    rpm_changelog = Path("packageroot/rpm/sista.spec").read_text().split("%changelog\n", 1)[1]
    first_rpm_entry = next((line for line in rpm_changelog.splitlines() if line.startswith("* ")), "")
    if not re.fullmatch(rf"\* .+ - {re.escape(base)}-{re.escape(rpm_release)}", first_rpm_entry):
        errors.append(f"packageroot/rpm/sista.spec: expected changelog version {base}-{rpm_release}")

    for error in errors:
        print(error, file=sys.stderr)
    return 1 if errors else 0


if __name__ == "__main__":
    sys.exit(main())
