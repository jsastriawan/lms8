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

# TODO:
- Packaging to deb/rpm
- Systemd init script
