# norootforbuild

%if 0%{?fedora_version}
%define breq qt4-devel, gstreamer-devel, gstreamer-plugins-base-devel
%define qmake /usr/bin/qmake-qt4
%define lrelease /usr/bin/lrelease-qt4
%endif  
%if 0%{?mandriva_version}
%define breq libqt4-devel, qt4-linguist, gstreamer0.10-devel, gstreamer0.10-plugins-base-devel
%define qmake /usr/lib/qt4/bin/qmake
%define lrelease /usr/lib/qt4/bin/lrelease
%endif
%if 0%{?suse_version}
%define breq update-desktop-files, libqt4-devel, gstreamer-0_10-devel, gstreamer-0_10-plugins-base-devel
%define qmake /usr/bin/qmake
%define lrelease /usr/bin/lrelease
%endif  

Summary:	Cuberok audio player
Name:		cuberok
Version:	0.0.10
Release:	0
License:	GPL
Group:		Audio
Source:		%{name}_%{version}.orig.tar.gz
BuildRoot:	%{_tmppath}/%{name}-%{version}-build  
Vendor:		Vasiliy Makarov <drmoriarty.0@gmail.com>
BuildRequires:	gcc-c++, taglib-devel, phonon-devel, %{breq}
Prefix:		/usr

%description
Cuberok is an audio player and a collection manager based on Qt4.

%if 0%{?mandriva_version} == 0
%debug_package
%endif

%prep
%setup -q

%build
%{qmake} "CONFIG+=player_phonon" Cuberok.pro
make 

%install
rm -rf $RPM_BUILD_ROOT
%{makeinstall} INSTALL_ROOT=%{buildroot}/usr
%if 0%{?suse_version}
%suse_update_desktop_file %{buildroot}%{_datadir}/applications/%{name}.desktop
%endif

%clean
rm -rf %{buildroot}

%files
%defattr(-,root,root)
%doc ChangeLog README license.txt
%{_bindir}/cuberok
%{_libdir}/cuberok
%{_datadir}/%{name}
%{_datadir}/applications/%{name}.desktop
%{_datadir}/pixmaps/%{name}.xpm

%changelog
* Tue May 19 2009 TI_Eugene <ti.eugene@gmail.com>
- Initial release for OBS

* Fri Apr 10 2009 Vasiliy Makarov <drmoriarty.0@gmail.com>
- First release for openSuse

  