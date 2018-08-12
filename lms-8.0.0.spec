Summary: The "Hello World" program from GNU
Name: lms
Version: 8.0.0
Release: 700%{?dist}
Source0: %{name}-%{version}.tar.gz
License: Proprietary tool
Group: System Services


%description 
The AMT LMS enables communication between userspace and Intel ME

%prep
%setup -q

%build
%configure --prefix=/usr
make 

%install
%make_install
mkdir -p %{buildroot}/lib/systemd/system
cp %{_builddir}/%{name}-%{version}/scripts/lms.service %{buildroot}/lib/systemd/system/lms.service

%files
/lib/systemd/system/lms.service
/etc/init.d/lms
/usr/bin/notifyDesktop.sh
/usr/sbin/lms
/usr/share/xml/AMTAlerts.xml

%pre
killall -9 lms

%post
[ -f /usr/bin/lms ] || rm -rf /usr/bin/lms
ln -s /usr/sbin/lms /usr/bin/lms
systemctl enable lms
systemctl start lms

