Summary: Cuberok audio player
Name: cuberok
Version: 0.0.1
Release: 0
Copyright: GPL
Group: Audio
Source: http://%{name}.googlecode.com/files/%{name}-%{version}.tar.gz
BuildRoot: /var/tmp/%{name}-rpmroot
Provides: cuberok
Packager: Vasiliy Makarov <drmoriarty.0@gmail.com>
#Requires:
BuildRequires: libqt4-devel, libtaglib-devel

%description
Cuberok is yet another audio player based on Qt4.

%prep
%setup
qmake Cuberok.pro

%build
LOCKINGTEST='/tmp .' make

%install
rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT/usr/{bin,share/doc/cuberok}
make INSTALL_ROOT=$RPM_BUILD_ROOT install

%files
%attr(4555,root,root) /usr/bin/cuberok
%defattr(-,root,root)
%doc /usr/share/doc/cuberok/*
%attr(0444,root,root) /usr/share/cuberok/*/*

%changelog
* Mon Dec 14 2008 Vasiliy Makarov <drmoriarty.0@gmail.com>
- built RPM and SRPM.
