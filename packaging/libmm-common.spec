
Name:       libmm-common
Summary:    Multimedia Framework Common Lib
Version:    0.2.19
Release:    1
Group:      TO_BE/FILLED_IN
License:    TO BE FILLED IN
Source0:    libmm-common-%{version}.tar.gz
Requires(post): /sbin/ldconfig
Requires(postun): /sbin/ldconfig
BuildRequires:  pkgconfig(glib-2.0)
BuildRequires:  pkgconfig(mm-log)


%description
Multimedia Framework Common Library



%package devel
Summary:    Multimedia Framework Common Lib (devel)
Group:      Development/Libraries
Requires:   %{name} = %{version}-%{release}

%description devel
Multimedia Framework Common Library (devel)



%package internal-devel
Summary:    Multimedia Framework Common Internal Lib (devel)
Group:      Development/Libraries
Requires:   %{name} = %{version}-%{release}

%description internal-devel
Multimedia Framework Common Library (devel)


%prep
%setup -q 

./autogen.sh
CFLAGS="%{optflags} -DEXPORT_API=\"__attribute__((visibility(\\\"default\\\")))\" " ./configure --prefix=%{_prefix} ; export CFLAGS

%build


make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
%make_install




%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig





%files
%defattr(-,root,root,-)
%{_libdir}/libmmfcommon.so.*


%files devel
%defattr(-,root,root,-)
%{_includedir}/mmf/SLP_MultimediaFW_PG.h
%{_includedir}/mmf/mm_types.h
%{_includedir}/mmf/mm_error.h
%{_includedir}/mmf/mm_message.h
%{_includedir}/mmf/mm.h
%{_libdir}/pkgconfig/mm-common.pc
%{_libdir}/libmmfcommon.so

%files internal-devel
%defattr(-,root,root,-)
%{_includedir}/mmf/mm_attrs.h
%{_includedir}/mmf/mm_attrs_private.h
%{_includedir}/mmf/mm_debug.h
