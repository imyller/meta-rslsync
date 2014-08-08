OpenEmbedded / Angstrom Distribution layer for BitTorrent Sync 
==============================================================

[BitTorrent&reg; Sync][1] from BitTorrent&reg; Inc. is a simple tool that
applies p2p protocol for direct live folder sync with maximum security, network
speed and storage capacity. It has native versions for Mac, Windows and Linux,
as well as native NAS integration.

BitTorrent&reg; Inc. __delivers for Linux users only a raw binary file without
any deployment concept or setup system__. It's up to the user to create a
reliable startup and shutdown logic and to manage a configuration file. Also a
dedicated GUI, as provided for Windows and Mac OSX is missing.

The scope of this project is to provide latest Bitbake package recipes for 
server version of BitTorrent Sync.

**THESE SOFTWARE IS UNOFFICIAL AND NOT THE WORK OF BITTORRENT&reg; INC.
PLEASE DO NOT CONTACT THE BITTORRENT&reg; INC. SUPPORT WITH QUESTIONS OR
PROBLEMS RELATED TO THE USE OF THE PACKAGES. YOU WILL FIND COMPETENT HELP
AND SUPPORT IN THE RELATED DISCUSSION THREAD IN THE SUPPORT FORUM (Links
below)**


Useful Links
============

- [Project Home Page][2]
- [BitTorrent Sync Home Page][1]
- [BitTorrent Sync Support Forum][3]

[1]: http://www.bittorrent.com/sync
[2]: http://www.yeasoft.com/site/projects:btsync-deb
[3]: http://forum.bittorrent.com/forum/107-bittorrent-sync/

Installation
============

1. Add `meta-btsync` layer to `sources/layers.txt`

    ```
      meta-btsync,git://github.com/imyller/meta-btsync.git,master,HEAD
    ```
    
2. Add `meta-btsync` layer to `EXTRALAYERS` in `conf/bblayers.conf`

    ```
        EXTRALAYERS +=" \
            ${TOPDIR}/sources/meta-btsync \
        "
    ```
  
3. Run `oebb.sh update`

Usage
=====

### Building Bittorrent Sync package

1. To build latest BitTorrent Sync package:

```
    bitbake btsync
```

Copyright and Legal Stuff
========================

BitTorrent® Sync is owned and developed by BitTorrent® Inc.
Copyright 2013, 2014 - BitTorrent Inc.
By using this application, you agree to BitTorrent's Inc. Privacy Policy and Terms.
http://www.bittorrent.com/legal/privacy
http://www.bittorrent.com/legal/terms-of-use

BitTorrent Sync Bitbake Packaging found in meta-btsync are developed and maintained by Ilkka Myller
Copyright 2014 - Ilkka Myller <ilkka.myller@nodefield.com>.
Released under MIT license. Please read the license conditions.
