# Halo CE Vita: AI Spartan Companion

An **experimental, unofficial community fork** of [Halo CE Vita by BirchWoodGod](https://github.com/BirchWoodGod/halo-ce-vita). This build adds a computer-controlled Spartan teammate to the Halo: Combat Evolved campaign on PS Vita.

**[Download Companion v0.1.0 (VPK)](https://github.com/ChatProductions/halo-ce-vitacoopbot/releases/tag/vita-coopbot-v0.1.0)** · [Release notes](https://github.com/ChatProductions/halo-ce-vitacoopbot/releases/tag/vita-coopbot-v0.1.0) · [Original project](https://github.com/BirchWoodGod/halo-ce-vita)

> **Version note:** v0.1.0 is built from the 1.1.0-era Vita port, **not upstream v1.1.1**. This is a separate experimental build, not an official update.

## Starting a campaign with the companion

1. Launch **Halo CE** on the Vita.
2. Open **Campaign**.
3. Choose **Select Mission**.
4. Highlight the mission you want and press **Triangle**. If the menu uses Xbox button labels, press the equivalent **Y** button.
5. The companion campaign loads automatically. You **do not** need to spawn the Spartan separately or wait for another player to join.

The companion has been reported working in both the **second** and **third** campaign missions. Other missions may need additional testing.

## What the companion can do

- Follow you and engage Covenant enemies using combat, reloading, melee, grenades, and experimental tactical weapon and ammo-selection behavior.
- Automatically enter a Warthog as **gunner** when possible, or ride as a passenger. It **does not drive**. Turret firing has been confirmed during gameplay.
- Attempt to stop endless idle turret rotation, avoid entering overturned Warthogs, and dismount when a vehicle flips. These newer fixes still need hardware testing.
- Use a separate experimental **Save & Quit / Resume** file, `savegame_companion.bin`, without replacing the standard solo save slot. Saving and resuming have been reported working.

## Known limitations

- The companion's walking animation can look like sliding.
- Passenger-seat shooting and the newest Warthog fixes are **not yet confirmed** on hardware.
- Companion behavior and campaign progress can still have bugs. Keep a backup of saved games.
- The preview is **not network-compatible with the original port's v1.1.1**.

## Installation

1. Download the **companion VPK** from [this fork's release page](https://github.com/ChatProductions/halo-ce-vitacoopbot/releases/tag/vita-coopbot-v0.1.0).
2. Install the VPK using **VitaShell**. It replaces the existing Halo CE application under title ID `HCEV00001`.
3. Keep your legally obtained Xbox Halo CE game files in `ux0:data/haloce-vita/`. Back up your saves before switching between official and experimental builds.

**No copyrighted Halo game files are bundled.** Consult the [original port's installation instructions](https://github.com/BirchWoodGod/halo-ce-vita#install) for the required game data and Vita prerequisites.

## Source, credits, and future updates

- **`main` is this fork's primary source branch.** The [older companion development branch](https://github.com/ChatProductions/halo-ce-vitacoopbot/tree/feat/campaign-companion-1_1-vita) remains for history.
- The downloadable v0.1.0 VPK was built from source commit `11baa666416672a10797fcd541631daeffe11a2f`, with later documentation changes.
- Updating the companion to upstream **v1.1.1** is a future task; it has **not** been completed.
- All credit for the underlying Vita port goes to [BirchWoodGod and its contributors](https://github.com/BirchWoodGod/halo-ce-vita). This fork adds experimental companion functionality. See [GPL-3.0 license](LICENSE).

