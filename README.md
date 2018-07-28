# Information

See [README](./README) for more detail.


# Compilation

```
./configure
make
```

# Running
```
sudo src/lms
```

# Packaging for Debian-based distribution

```
debuild --no-tgz-check -b -us -uc
```

Resulting Debian package is at ../lms8_8.0.0-700_amd64.deb

# Packaging for RPM-based distribution
```
mkdir -p ~/rpmbuild/{SPECS,SOURCES}
./configure
make dist-gzip
cp lms-8.0.0.tar.gz ~/rpmbuild/SOURCES
cp lms-8.0.0.spec ~/rpmbuild/SPECS
cd ~/rpmbuild/SPECS
rpmbuild -ba lms-8.0.0.spec
```
The resulting RPMS will be at ~/rpmbuild/RPMS/x86_64/lms-8.0.0-700.x86_64.rpm

# TODO:
- Packaging to ~~deb/rpm~~
- ~~Systemd init script~~
- Testing package quality for both deb and rpm packages
