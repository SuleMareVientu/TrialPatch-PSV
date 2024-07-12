This plugin turns game trials into the full game.  
Same as "Upgradable App Debug" option in Test Kits (forces NPDRM License SKU flag to FULL_GAME).  
See: https://docs.vitasdk.org/group__SceNpDrmKernel.html#structSceNpDrmLicense  
One could also patch `sceAppMgrAppParamGetInt(pid, 2, val)` to return 3 at a kernel level.

# Installation:
#### Add plugin path to the *TITLE_ID or *ALL section.
