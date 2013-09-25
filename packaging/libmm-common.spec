Name:       libmm-common
Version:    0.2.54
Release:    0
Summary:    Multimedia Framework Common Library
Group:      Multimedia Framework/Libraries
License:    Apache-2.0
Source0:    %{name}-%{version}.tar.gz
Source1001: 	libmm-common.manifest
BuildRequires:  pkgconfig(glib-2.0)
BuildRequires:  pkgconfig(mm-log)

%description
Multimedia Framework Common Library

%package devel
Summary:    Multimedia Framework Common Lib (devel)
Group:      Development/Libraries
Requires:   %{name} = %{version}

%description devel
Multimedia Framework Common Library (devel)

%prep
%setup -q
cp %{SOURCE1001} .

%build

./autogen.sh
CFLAGS="%{optflags} -DEXPORT_API=\"__attribute__((visibility(\\\"default\\\")))\" " %configure
make %{?_smp_mflags}

%install
%make_install


%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig


%files
%manifest %{name}.manifest
%defattr(-,root,root,-)
%{_libdir}/libmmfcommon.so.*


%files devel
%manifest %{name}.manifest
%defattr(-,root,root,-)
%{_includedir}/mmf/SLP_MultimediaFW_PG.h
%{_includedir}/mmf/mm_types.h
%{_includedir}/mmf/mm_error.h
%{_includedir}/mmf/mm_message.h
%{_includedir}/mmf/mm_attrs.h
%{_includedir}/mmf/mm_attrs_private.h
%{_includedir}/mmf/mm_debug.h
%{_includedir}/mmf/mm.h
%{_libdir}/pkgconfig/mm-common.pc
%{_libdir}/libmmfcommon.so