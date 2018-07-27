#ifndef _DEFAULTALERTS_H
#define _DEFAULTALERTS_H
#define DEFAULT_ALERTS_LENGTH 6257
#define DEFAULT_ALERTS "iAMT0001-:System Defense Policy triggered.;iAMT0002-:Agent Presence Agent not started.;iAMT0003-:Agent Presence Agent stopped.;iAMT0004-:Agent Presence: running.;\
iAMT0005-:Agent Presence: expired.;iAMT0006-:Agent Presence: suspended.;iAMT0007-:Host software attempt to disable AMT Network link detected.;\
iAMT0008-:Host software attempt to disable AMT Network link detected -- Host Network link blocked.;iAMT0009-:AMT clock or FLASH wear-out protection disabled.;\
iAMT0010-:Intel(R) AMT Network Interface: Heuristics defense slow threshold trespassed.;iAMT0011-:Intel(R) AMT Network Interface: Heuristics defense fast threshold trespassed.;\
iAMT0012-:Intel(R) AMT Network Interface: Heuristics defense factory defined threshold trespassed.;iAMT0013-:Intel(R) AMT Network Interface: Heuristics defense Encounter timeout expired.;\
iAMT0014-:General certificate error.;iAMT0015-:Certificate expired.;iAMT0016-:No trusted root certificate.;iAMT0017-:Not configured to work with server certificate.;iAMT0018-:Certificate revoked.;\
iAMT0019-:RSA exponent too large.;iAMT0020-:RSA modulus too large.;iAMT0021-:Unsupported digest.;iAMT0022-:Distinguished name too long.;iAMT0023-:Key usage missing.;\
iAMT0024-:General SSL handshake error.;iAMT0025-:General 802.1x error.;iAMT0026-:AMT Diagnostic AlertEAC error - General NAC error.;\
iAMT0027-:AMT Diagnostic AlertEAC error - attempt to get a NAC posture while AMT NAC is disabled.;iAMT0028-:AMT Diagnostic AlertEAC error - attempt to get a posture of an unsupported type.;\
iAMT0029-:Audit log storage is 50% full.;iAMT0030-:Audit log storage is 75% full.;iAMT0031-:Audit log storage is 85% full.;iAMT0032-:Audit log storage is 95% full.;\
iAMT0033-:Audit log storage is full.;iAMT0034-:Firmware Update Event - Partial.;iAMT0035-:Firmware Update Event - Failure.;iAMT0036-:Remote connectivity initiated.;\
iAMT0037-:ME Presence event.;iAMT0038-0:AMT is being unprovisioned using BIOS command.;iAMT0038-1:AMT is being unprovisioned using Local MEI command.;\
iAMT0038-2:AMT is being unprovisioned using Local WS-MAN/SOAP command.;iAMT0038-3:AMT is being unprovisioned using Remote WS-MAN/SOAP command.;\
iAMT0050-:User Notification Alert - General Notification.;iAMT0050-16:User Notification Alert - Circuit Breaker notification (CB Drop TX filter hit.).;\
iAMT0050-17:User Notification Alert - Circuit Breaker notification (CB Rate Limit TX filter hit.).;iAMT0050-18:User Notification Alert - Circuit Breaker notification (CB Drop RX filter hit.).;\
iAMT0050-19:User Notification Alert - Circuit Breaker notification (CB Rate Limit RX filter hit.).;iAMT0050-32:User Notification Alert - EAC notification.;\
iAMT0050-48:User Notification Alert - Remote diagnostics - (Remote Redirection session started - SOL).;iAMT0050-49:User Notification Alert - Remote diagnostics - (Remote Redirection session stopped - SOL).;\
iAMT0050-50:User Notification Alert - Remote diagnostics. (Remote Redirection session started - IDE-R).;iAMT0050-51:User Notification Alert - Remote diagnostics. (Remote Redirection session stopped - IDE-R).;\
iAMT0050-66:User Notification Alert - WLAN notification (Host profile mismatch - Management Interface ignored).;\
iAMT0050-67:User Notification Alert - WLAN notification (Management device overrides host radio).;iAMT0050-68:User Notification Alert - WLAN notification (Host profile security mismatch).;\
iAMT0050-69:User Notification Alert - WLAN notification (Management device relinquishes control over host Radio).;iAMT0051-:User Notification Alert - SecIo event.;\
iAMT0051-0:User Notification Alert - SecIo event semaphore at host.;iAMT0051-1:User Notification Alert - semaphore at ME.;iAMT0051-2:User Notification Alert - SecIo event - semaphore timeout.;\
iAMT0052-:User Notification Alert - KVM session event.;iAMT0052-0:User Notification Alert - KVM session requested.;iAMT0052-1:User Notification Alert - KVM session started.;\
iAMT0052-2:User Notification Alert - KVM session stopped.;iAMT0053-:User Notification Alert - RCS notification.;\
iAMT0053-50:User Notification Alert - RCS notification (HW button pressed. Connection initiated automatically).;\
iAMT0053-52:User Notification Alert - RCS notification (HW button pressed. Connection wasn't initiated automatically).;iAMT0053-53:User Notification Alert - RCS notification (Contracts updated).;\
iAMT0054-:User Notification Alert - WLAN notification. Wireless Profile sync enablement state changed.;iAMT0055-:User Notification Alert - Provisioning state change notification.;\
iAMT0055-0:User Notification Alert - Provisioning state change notification - Pre-configuration.;iAMT0055-1:User Notification Alert - Provisioning state change notification - In configuration.;\
iAMT0055-2:User Notification Alert - Provisioning state change notification - Post-configuration.;\
iAMT0055-3:User Notification Alert - Provisioning state change notification - unprovision process has started.;iAMT0056-:User Notification Alert - System Defense change notification.;\
iAMT0057-:User Notification Alert - Network State change notification.;iAMT0058-:User Notification Alert - Remote Access change notification.;\
iAMT0058-1:User Notification Alert - Remote Access change notification - tunnel is closed.;iAMT0058-1:User Notification Alert - Remote Access change notification - tunnel is open.;\
iAMT0059-:User Notification Alert - KVM enabled event.;iAMT0059-0:User Notification Alert - KVM enabled event - KVM disabled.;\
iAMT0059-1:User Notification Alert - KVM enabled event - KVM enabled (both from MEBx and PTNI).;iAMT0060-:User Notification Alert - SecIO configuration event.;iAMT0061-:ME FW reset occurred.;\
iAMT0062-:User Notification Alert - IpSyncEnabled event.;iAMT0062-0:User Notification Alert - IpSyncEnabled event - IpSync disabled.;\
iAMT0062-1:User Notification Alert - IpSyncEnabled event - IpSync enabled.;iAMT0063-:User Notification Alert - HTTP Proxy sync enabled event.;\
iAMT0063-0:User Notification Alert - HTTP Proxy sync enabled event - HTTP Proxy Sync disabled.;iAMT0063-1:User Notification Alert - HTTP Proxy sync enabled event - HTTP Proxy Sync enabled.;\
iAMT0064-:User Notification Alert - User Consent event.;iAMT0064-1:User Notification Alert - User Consent event - User Consent granted.;\
iAMT0064-2:User Notification Alert - User Consent event - User Consent ended.;"
#endif
