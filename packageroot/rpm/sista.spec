Name:           sista
Version:        %{?sista_version}%{!?sista_version:3.0.1}
Release:        %{?sista_release}%{!?sista_release:1}%{?dist}
# The upstream build does not emit debug information. Disable automatic debug
# subpackage generation rather than failing on an empty debugsource file.
%global debug_package %{nil}
Summary:        Lightweight C++ library for terminal games and animations
License:        MIT
URL:            https://github.com/FLAK-ZOSO/Sista
Source0:        %{name}-%{version}.tar.gz

BuildRequires:  gcc-c++
BuildRequires:  make

%description
Sista is a lightweight C++ library with a C API for building terminal games
and animations. It provides terminal ANSI helpers plus field and pawn
primitives.

%prep
%autosetup

%build
make build FULL_VERSION=%{?sista_full_version}%{!?sista_full_version:%{version}}

%install
rm -rf %{buildroot}
make install FULL_VERSION=%{?sista_full_version}%{!?sista_full_version:%{version}} PREFIX=/usr DESTDIR=%{buildroot}
# RPM's dependency generator scans executable shared objects. The libraries
# themselves need this mode too, so their SONAME Provides are recorded.
find %{buildroot}%{_prefix}/lib -type f -name '*.so.*' -exec chmod 755 {} +
rm -f %{buildroot}%{_sysconfdir}/ld.so.conf.d/sista.conf
rmdir --ignore-fail-on-non-empty %{buildroot}%{_sysconfdir}/ld.so.conf.d 2>/dev/null || :
rmdir --ignore-fail-on-non-empty %{buildroot}%{_sysconfdir} 2>/dev/null || :

%files
%license LICENSE.md
%doc README.md ReleaseNotes.md changelog.md
%{_includedir}/sista/
%{_prefix}/lib/libSista.so
%{_prefix}/lib/libSista.so.*
%{_prefix}/lib/libSista.a
%{_prefix}/lib/libSista_api.so
%{_prefix}/lib/libSista_api.so.*
%{_prefix}/lib/libSista_api.a

%changelog
* Thu Jul 30 2026 FLAK-ZOSO <mattia.marchese.2006@gmail.com> - 3.0.1-1
- Initial RPM package
