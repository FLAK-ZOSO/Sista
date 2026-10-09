Name:           sista
Version:        %{?sista_version}%{!?sista_version:3.1.0}
Release:        %{?sista_release}%{!?sista_release:1}%{?dist}
# Shared libraries are stripped by install-strip below. Disable automatic
# debug subpackages rather than failing on an empty debugsource file.
%global debug_package %{nil}
Summary:        Lightweight C++ library for terminal games and animations
License:        GPL-3.0-only
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
make install-strip FULL_VERSION=%{?sista_full_version}%{!?sista_full_version:%{version}} PREFIX=%{_prefix} LIBDIR=%{_libdir} DESTDIR=%{buildroot}
# RPM's dependency generator scans executable shared objects. The libraries
# themselves need this mode too, so their SONAME Provides are recorded.
find %{buildroot}%{_libdir} -type f -name '*.so.*' -exec chmod 755 {} +
rm -f %{buildroot}%{_sysconfdir}/ld.so.conf.d/sista.conf
rmdir --ignore-fail-on-non-empty %{buildroot}%{_sysconfdir}/ld.so.conf.d 2>/dev/null || :
rmdir --ignore-fail-on-non-empty %{buildroot}%{_sysconfdir} 2>/dev/null || :

%files
%license LICENSE.md
%doc README.md ReleaseNotes.md changelog.md
%{_includedir}/sista/
%{_libdir}/libSista.so
%{_libdir}/libSista.so.*
%{_libdir}/libSista.a
%{_libdir}/libSista_api.so
%{_libdir}/libSista_api.so.*
%{_libdir}/libSista_api.a
%{_mandir}/man3/*
%{_mandir}/man7/sista.7*

%changelog
* Fri Oct 09 2026 FLAK-ZOSO <mattia.marchese.2006@gmail.com> - 3.1.0-1
- Build libraries by default and add conventional Make targets.
- Include section 3 and section 7 man pages in the RPM.

* Fri Jul 31 2026 FLAK-ZOSO <mattia.marchese.2006@gmail.com> - 3.0.3-1
- Add EL9-compatible RPM distribution packaging.
- Correct the RPM license metadata to GPL-3.0-only.

* Thu Jul 30 2026 FLAK-ZOSO <mattia.marchese.2006@gmail.com> - 3.0.1-1
- Initial RPM package
