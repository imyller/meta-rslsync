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

SRC_URI[md5sum] = "a34c00bed04f24686a4bcdf7d8d2aadf"
SRC_URI[sha256sum] = "6e0e5886c984b142fa17351c0cc062750e1a2c4edad8fbddc115be466abbd7ea"

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
