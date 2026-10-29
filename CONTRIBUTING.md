# Contributing to Halo CE Vita: AI Spartan Companion

Thanks for helping improve the companion. This is an **unofficial experimental fork** of [BirchWoodGod's Halo CE Vita](https://github.com/BirchWoodGod/halo-ce-vita).

The default **`main` branch** contains our current companion source. The downloadable [v0.1.0 VPK](https://github.com/ChatProductions/halo-ce-vitacoopbot/releases/tag/vita-coopbot-v0.1.0) was compiled from commit [`11baa666`](https://github.com/ChatProductions/halo-ce-vitacoopbot/commit/11baa666416672a10797fcd541631daeffe11a2f); subsequent changes to `main` have been documentation and release-workflow updates, not new companion behavior.

**Current base:** Halo CE Vita 1.1.0-era code. **Upstream 1.1.1 has not yet been integrated.** Please say which base you are using when you open an issue or PR.

## Get started

1. Fork [this repository](https://github.com/ChatProductions/halo-ce-vitacoopbot) and make a feature branch from `main`.
2. Read the [README](README.md) for the companion's controls, current behavior, and limitations.
3. Keep each pull request focused: for example, one vehicle fix, one AI improvement, or one upstream migration step.
4. Explain what changed, why, and how you tested it. Link related issues.
5. Do not upload Microsoft/Bungie game maps, `default.xbe`, BIOS files, or other copyrighted game assets. Contributors need their own legally obtained Xbox Halo CE game files to run the port.

Code is distributed under the repository's [GPL-3.0 license](LICENSE). Retain required license and attribution notices.

## Build the Vita version

The repository includes a [Vita companion test build workflow](.github/workflows/vita-companion-test.yml). It uses the `vitasdk/vitasdk:2026.08` container, configures the project, and runs `ninja vita`.

For a manual build **inside an appropriate VitaSDK environment**, the workflow's build commands are:

```sh
python3 configure.py --lto off --pgo off --portable --release
ninja vita
```

Expected outputs:

- `build/vita/halo.vpk`
- `build/vita/eboot.bin`

You can also use **Actions → Vita companion test build → Run workflow** on `main` to request a CI build. Its downloadable test artifacts expire after **three days**, so do not treat them as permanent releases. An Actions compilation success **does not prove the companion works correctly on real Vita hardware**.

Install experimental VPKs with VitaShell and back up your saves before switching versions. This port uses title ID `HCEV00001` and game data under `ux0:data/haloce-vita/`.

## Where the companion code lives

| Path | What to look for |
| --- | --- |
| `port/linux/game/bots.c` | Existing bot framework plus companion AI, combat, movement, and vehicle decisions |
| `port/linux/include/bots.h` | Bot interface and campaign integration |
| `port/linux/src/port_config.c` | Relevant configuration integration |
| `source/interface/ui_widget_event_handler_functions.c` | Campaign UI behavior |
| `source/saved games/game_state.c`, `game_state.h`, `game_state_xbox.c` | Companion checkpoint / Save & Quit state |
| `port/vita/` | Vita-specific input, platform code, and packaging |
| `.github/workflows/vita-companion-test.yml` | Reproducible Vita build workflow |

Study existing interfaces before changing player allocation, network co-op state, vehicle seats, or save serialization. These systems are interconnected.

## Testing and bug reports

To start a companion campaign in the published Vita preview:

1. **Campaign → Select Mission**.
2. Highlight a mission and press **Triangle** (or **Y** in Xbox-labeled menus).
3. The companion mission should load automatically; no manual bot spawn is needed.

Community testing has reported that the companion works in **mission 2 and mission 3**. Warthog turret fire and experimental Save & Quit/Resume have also been reported working. This is not yet a full-campaign compatibility claim.

Please prioritize these regression checks:

- Does the companion follow, aim, attack, reload, and recover when it runs out of ammunition?
- Does Warthog gunner targeting remain stable instead of rotating continuously?
- Can the player flip an overturned Warthog without the bot blocking vehicle interaction?
- Does the companion fire appropriately from the passenger seat?
- Does the companion remain out of the driver's seat?
- Do checkpoints and Save & Quit/Resume work without damaging normal solo saves?
- Does the companion animate while moving, rather than sliding?
- Does friendly fire behave as expected for the underlying game?

When reporting a bug, include:

- **Build:** release version or exact commit SHA; Vita model and relevant settings.
- **Mission/checkpoint:** where it happened.
- **Steps to reproduce:** numbered steps, including vehicle seat and weapon when relevant.
- **Expected versus actual result**, and whether it happens every time.
- **Evidence:** a short video/screenshot and relevant logs if available.

Useful Vita logs may include `ux0:data/haloce-vita/halo.log` and `ux0:data/haloce-vita/data/debug.txt`. Attach crash dumps if generated. **Inspect logs before publishing:** remove personal network addresses, passwords, invitation tokens, and unrelated private information. Do not publish `host_invite.txt` or other access tokens.

## Porting the companion to upstream 1.1.1

**Please start from a clean branch based on [upstream v1.1.1](https://github.com/BirchWoodGod/halo-ce-vita/releases/tag/v1.1.1), then integrate companion changes selectively.** Do not overwrite upstream `bots.c` wholesale with our older file: 1.1.1 substantially expands that code and adds `bots_nav.c` and `bots_squads.c`.

A useful migration PR should:

1. Preserve the newer upstream bot navigation, squads, menus, and multiplayer behavior.
2. Reintroduce campaign companion creation and AI updates without interfering with normal multiplayer bots.
3. Reconcile Warthog boarding and turret behavior with the newer engine.
4. Reconcile companion checkpoint saves with the newer game-state code; avoid assuming old serialized saves are compatible.
5. Keep the Vita build working, then test missions 2 and 3 and the checks above on hardware.
6. Explain any remaining regressions. **Do not label an untested build as a working 1.1.1 companion release.**

Small, reviewable PRs are especially welcome. You do **not** need write access to this repository to fork it and submit a PR.

## Scope and credits

The immediate priority is a reliable **PS Vita companion**. Changes that help Windows or Android are welcome when separated clearly, but they should not break Vita. The companion **does not need to drive vehicles**.

Please preserve attribution to the original [Halo CE Vita authors and contributors](https://github.com/BirchWoodGod/halo-ce-vita). This project is not endorsed by the original game rights holders or the upstream port developer.
