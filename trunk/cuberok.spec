Summary: Cuberok audio player
Name: cuberok
Version: 0.0.8
Release: 0
#Copyright: GPL
License: GPL
Group: Audio
Source: %{name}_%{version}.orig.tar.gz
BuildRoot: %{_tmppath}/%{name}-%{version}-build  
#BuildRoot: /var/tmp/%{name}-rpmroot
#Provides: cuberok
Packager: Vasiliy Makarov <drmoriarty.0@gmail.com>
#Requires:
BuildRequires: libqt4-devel, taglib-devel, phonon-devel, gstreamer-0_10-devel, gstreamer-0_10-plugins-base-devel

%if 0%{?suse_version}
BuildRequires: update-desktop-files
%endif

%description
Cuberok is yet another audio player based on Qt4.

%prep
%setup
qmake "CONFIG+=player_phonon" Cuberok.pro

%build
#LOCKINGTEST='/tmp .' make 
make 

%install
rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT/usr/{bin,share/doc/cuberok}
make INSTALL_ROOT=$RPM_BUILD_ROOT/usr install
install -m 644 -p README $RPM_BUILD_ROOT/usr/share/doc/cuberok/
install -m 644 -p ChangeLog $RPM_BUILD_ROOT/usr/share/doc/cuberok/
%if 0%{?suse_version}  
%suse_update_desktop_file $RPM_BUILD_ROOT/usr/share/applications/%{name}.desktop
%endif

%clean
rm -rf "$RPM_BUILD_ROOT"

%files
%attr(0555,root,root) %{_bindir}/cuberok
%defattr(-,root,root)
%{_libdir}/cuberok
%{_datadir}/%{name}/
%{_datadir}/%{name}/locale/
%{_datadir}/doc/%{name}/
%doc %{_datadir}/doc/cuberok/*
%attr(0444,root,root) %{_libdir}/cuberok/*
%attr(0444,root,root) %{_datadir}/applications/*
%attr(0444,root,root) %{_datadir}/cuberok/locale/*
%attr(0444,root,root) %{_datadir}/pixmaps/*

%changelog
* Fri Apr 10 2009 Vasiliy Makarov <drmoriarty.0@gmail.com>
- First release for openSuse
