#!/usr/bin/env bash
set -euo pipefail

repository_root=$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)
version=${SISTA_VERSION:-$(sed -n 's/^#define SISTA_VERSION "\([^"]*\)"/\1/p' "$repository_root/include/sista/version.hpp")}

if [[ -z "$version" ]]; then
  echo "Could not determine the Sista version." >&2
  exit 1
fi

rpm_version=${version%%-*}
rpm_release=1
if [[ "$version" == *-* ]]; then
  rpm_release="0.${version#*-}"
fi

topdir=${RPM_TOPDIR:-"$repository_root/rpmbuild"}
mkdir -p "$topdir/SOURCES" "$topdir/SPECS"

# GitHub mounts the checkout in a container with a different owner. Trust only
# this known repository for the archive command; do not change global config.
git -c safe.directory="$repository_root" -C "$repository_root" archive --format=tar --prefix="sista-$rpm_version/" HEAD \
  | gzip -n > "$topdir/SOURCES/sista-$rpm_version.tar.gz"
cp "$repository_root/packageroot/rpm/sista.spec" "$topdir/SPECS/sista.spec"

rpmbuild -bb "$topdir/SPECS/sista.spec" \
  --define "_topdir $topdir" \
  --define "sista_version $rpm_version" \
  --define "sista_release $rpm_release" \
  --define "sista_full_version $version"
