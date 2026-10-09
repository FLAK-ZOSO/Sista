#!/usr/bin/env python3
"""Check the maintained man pages and compile their example programs."""

from pathlib import Path
import re
import subprocess
import sys
import typing


ROOT = Path(__file__).resolve().parents[1]
PAGES = sorted((ROOT / "docs/man").glob("*.[37]"))
TITLE = re.compile(r'^\.TH (\S+) ([37]) "(\d{4}-\d{2}-\d{2})" "Sista"$')
HEADING = re.compile(r"^\.SH (.+)$")


def check_page(page: Path) -> list[str]:
    problems: list[str] = []
    lines = page.read_text(encoding="utf-8").splitlines()
    match = TITLE.fullmatch(lines[0]) if lines else None
    if not match or match.group(1).lower() != page.stem or match.group(2) != page.suffix[1:]:
        problems.append(".TH title, section, date, or source is invalid")

    headings = [(index, found.group(1)) for index, line in enumerate(lines)
                if (found := HEADING.fullmatch(line))]
    names = [name for _, name in headings]
    required = ["NAME", "DESCRIPTION", "SEE ALSO"]
    if page.suffix == ".3":
        required.extend(["LIBRARY", "SYNOPSIS"])
    for name in required:
        if names.count(name) != 1:
            problems.append(f"expected exactly one {name} section")
    if names and (names[0] != "NAME" or names[-1] != "SEE ALSO"):
        problems.append("NAME must be first and SEE ALSO must be last")
    if page.suffix == ".3" and all(name in names for name in ("LIBRARY", "SYNOPSIS", "DESCRIPTION")):
        if not (names.index("LIBRARY") < names.index("SYNOPSIS") < names.index("DESCRIPTION")):
            problems.append("LIBRARY, SYNOPSIS, and DESCRIPTION are out of order")
    if "NAME" in names:
        name_line = lines[headings[names.index("NAME")][0] + 1]
        if not name_line.startswith(f"{page.stem} \\- "):
            problems.append("NAME must begin with the page name, \\-, and a description")
    for index, line in enumerate(lines, 1):
        if len(line) > 75:
            problems.append(f"line {index} exceeds 75 columns")

    rendered = subprocess.run(
        ["groff", "-man", "-Tutf8", "-ww", str(page)],
        capture_output=True, text=True, check=False,
    )
    if rendered.returncode or rendered.stderr.strip():
        problems.append(f"groff: {rendered.stderr.strip() or rendered.returncode}")

    if "EXAMPLES" in names:
        start = headings[names.index("EXAMPLES")][0] + 1
        end = headings[names.index("EXAMPLES") + 1][0]
        example = lines[start:end]
        if ".nf" in example and ".fi" in example:
            code = "\n".join(example[example.index(".nf") + 1:example.index(".fi")])
            code = code.replace(r"\en", r"\n") + "\n"
            compiler = "cc" if page.name == "sista-c-api.3" else "c++"
            standard = "-std=c11" if compiler == "cc" else "-std=c++17"
            compiled = subprocess.run(
                [compiler, standard, "-Wall", "-Wextra", "-Werror", "-Iinclude",
                 "-fsyntax-only", "-x", "c" if compiler == "cc" else "c++", "-"],
                cwd=ROOT, input=code, capture_output=True, text=True, check=False,
            )
            if compiled.returncode:
                problems.append(f"example does not compile: {compiled.stderr.strip()}")
        else:
            problems.append("EXAMPLES needs a no-fill code block")
    return problems


def main() -> int:
    if not PAGES or not any(page.suffix == ".7" for page in PAGES):
        print("Expected section-3 pages and a section-7 overview", file=sys.stderr)
        return 1
    failures = [(page, issue) for page in PAGES for issue in check_page(page)]
    header = (ROOT / "include/sista/api.h").read_text(encoding="utf-8")
    declarations = set(re.findall(
        r"^[^/\n]*\b(sista_[A-Za-z0-9_]+)\s*\(", header, re.MULTILINE,
    ))
    makefile = (ROOT / "Makefile").read_text(encoding="utf-8")
    alias_block = re.search(r"^MAN_ALIAS_SPECS = (.*?)(?:\n\n)", makefile, re.MULTILINE | re.DOTALL)
    aliases: set[typing.Any] = set(re.findall(r"\b(sista_[A-Za-z0-9_]+)=sista-c-api\.3", alias_block.group(1))) if alias_block else set()
    for name in sorted(declarations - aliases):
        failures.append((ROOT / "Makefile", f"missing C API man alias for {name}"))
    for name in sorted(aliases - declarations):
        failures.append((ROOT / "Makefile", f"man alias has no C API declaration: {name}"))
    for page, issue in failures:
        print(f"{page.relative_to(ROOT)}: {issue}", file=sys.stderr)
    if failures:
        return 1
    print(f"Validated {len(PAGES)} man pages and their examples")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
