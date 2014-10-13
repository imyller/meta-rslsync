DESCRIPTION = "BitTorrent Sync is a simple tool that applies p2p protocol for direct live folder sync with maximum security, network speed and storage capacity"
SECTION = "network"

LICENSE = "Proprietary"

LIC_FILES_CHKSUM = "file://LICENSE.TXT;md5=4b2e12dbe1b2dcec6a731f5af7f0da1a"

PR = "r1"

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

S = "${WORKDIR}"

SRC_URI = " \
        http://syncapp.bittorrent.com/${PV}/btsync_${TARGET_ARCH}-${PV}.tar.gz\
	file://btsync.conf\
	file://btsync.init\
"

SRC_URI[md5sum] = "e83a36a1c406cc32ada23507d510a8cf"
SRC_URI[sha256sum] = "6a18a36d099f78358998a1532e7162e641af83e37cb5faddd73fae00107abbb7"

INSANE_SKIP_${PN} += "ldflags"
INSANE_SKIP_${PN} += "already-stripped"

inherit update-rc.d

INITSCRIPT_NAME = "btsync"
INITSCRIPT_PARAMS = "defaults"

do_install() {
	
	install -d ${D}${sbindir}
	install -m 0755 ${WORKDIR}/btsync ${D}${sbindir}/

	install -d ${D}/var/lib/btsync

	install -d ${D}install -d ${D}${sysconfdir}/init.d
        install -m 0755 ${WORKDIR}/btsync.init ${D}${sysconfdir}/init.d/btsync

	install -d ${D}${sysconfdir}/btsync
	install -m 0655 ${WORKDIR}/btsync.conf ${D}${sysconfdir}/btsync/

	# Hack to fix missing ld-linux.so.3 symlink in /lib
	# Warning: currently this is not generic as it symlinks with armhf lib 
	install -d ${D}/lib	
	ln -sf ld-linux-armhf.so.3 ${D}/lib/ld-linux.so.3
  
}

FILES_${PN} = " \
	${sbindir}/btsync \
	${sysconfdir}/btsync/btsync.conf \
        ${sysconfdir}/init.d/btsync \
	/lib/ld-linux.so.3 \
	/var/lib/btsync \
"
