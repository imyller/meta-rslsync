[![Flattr this git repo](http://api.flattr.com/button/flattr-badge-large.png)](https://flattr.com/submit/auto?user_id=imyller&url=https://github.com/imyller/meta-btsync&title=meta-btsync&language=&tags=github&category=software)
OpenEmbedded recipe layer for BitTorrent Sync 
=============================================

[BitTorrent&reg; Sync][1] from BitTorrent&reg; Inc. is a simple tool that
applies p2p protocol for direct live folder sync with maximum security, network
speed and storage capacity. It has native versions for Mac, Windows and Linux,
as well as native NAS integration.

BitTorrent&reg; Inc. __delivers for Linux users only a raw binary file without
any deployment concept or setup system__. It's up to the user to create a
reliable startup and shutdown logic and to manage a configuration file. Also a
dedicated GUI, as provided for Windows and OS X is missing.

The scope of this project is to provide latest Bitbake package recipes for 
server version of BitTorrent Sync.

**THESE SOFTWARE IS UNOFFICIAL AND NOT THE WORK OF BITTORRENT&reg; INC.
PLEASE DO NOT CONTACT THE BITTORRENT&reg; INC. SUPPORT WITH QUESTIONS OR
PROBLEMS RELATED TO THE USE OF THE PACKAGES. YOU WILL FIND COMPETENT HELP
AND SUPPORT IN THE RELATED DISCUSSION THREAD IN THE SUPPORT FORUM (Link
below)**


Useful Links
============

- [BitTorrent Sync Home Page][1]
- [BitTorrent Sync Support Forum][2]

[1]: http://www.bittorrent.com/sync
[2]: http://forum.bittorrent.com/forum/107-bittorrent-sync/

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

### Building BitTorrent Sync package

1. To build latest BitTorrent Sync package:

```
    bitbake btsync
```
