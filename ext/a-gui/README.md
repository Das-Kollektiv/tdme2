[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://github.com/andreasdr/a-gui/blob/master/LICENSE)
[![NIX Build Status](https://github.com/andreasdr/a-gui/actions/workflows/nix.yml/badge.svg)](https://github.com/andreasdr/a-gui/actions)
[![MacOSX Build Status](https://github.com/andreasdr/a-gui/actions/workflows/macosx.yml/badge.svg)](https://github.com/andreasdr/a-gui/actions)
[![Windows/MINGW Build Status](https://github.com/andreasdr/a-gui/actions/workflows/windows-mingw.yml/badge.svg)](https://github.com/andreasdr/a-gui/actions)
[![Windows/MSC Build Status](https://github.com/andreasdr/a-gui/actions/workflows/windows-msc.yml/badge.svg)](https://github.com/andreasdr/a-gui/actions)
[![Coverity Scan Build Status](https://scan.coverity.com/projects/15611/badge.svg)](https://scan.coverity.com/projects/andreasdr-a-gui)  

![LOGO](https://raw.githubusercontent.com/andreasdr/a-gui/main/resources/github/agui-logo.png)
  
This is the home of A-GUI - C++ based graphical user interface for games

This document and repository is WIP. Expect a BETA release around 2025-03-01.
See section 3. for BETA release TODO list.

# 1. Introduction

A-GUI is developed as part of our [TDME2 3D Engine](https://github.com/andreasdr/tdme2) to match
the requirements for stunning game graphical user interfaces.

- A-GUI is open source
  - please check the [license](https://github.com/andreasdr/a-gui/blob/master/LICENSE)
  - you find the source code at [https://github.com/andreasdr/a-gui](https://github.com/andreasdr/a-gui) 
  - For A-GUI GUI XML documentation see [README-GUI-XML.md](./README-GUI-XML.md)
  - For A-GUI GUI MiniScript documentation see [README-MiniScript.md](./README-MiniScript.md)

# 2. Features
- borrows some ideas from Nifty-GUI regarding XML and layouting
- borrows some ideas from AngularJS like
    - all nodes are in the GUI node tree and can be made visible or unvisible depending on conditions
- adds some improvements like
    - support auto keyword with nodes width and height attributes
    - layouting on demand in combination with conditions
- supported primitive nodes from which compounds are built of
    - element
    - gradient
    - image(plus framebuffer and texture image nodes) 
    - input
    - layer
    - layout
    - panel
    - scrollbars
    - space
    - table
    - text + multiline/styled text
    - video
- supports custom templates and compound elements defined by templates and its controllers
    - compound elements
        - button
        - checkbox
        - dropdown
        - grid (needs some love still)
        - image button
        - input
        - knob
        - menu
        - progress bar
        - radio button
        - scrollarea
        - selectbox including tree view
        - selector horizontal
        - slider horizontal
        - slider vertical
        - tabs
        - moveable
    - supports custom templates in general
    - supports overriding used template of a compound element while using its controller
    - so TDME2 GUI is fully customizable in terms of appearance by modifying or adding XML template definitions
- includes a simple script language
    - to react on events with like on-mouse-click, ... and on-change for elements
    - to manipulate conditions of elements, values of element controller and node properties
- a MiniScript script can be attached to screen nodes
    - to react on events
    - to modify the gui nodes tree or gui nodes state
    - to implement GUI application flow(WIP)
- supports position and color based effects in combination with conditions that can also be defined via XML
- unicode support via UTF8

# 3. What is WIP or planned for first BETA
- GUI effects via XML definitions (already working, needs bugfixes)
- Some UI elements need some focus/disabled fixes
- ...

# 4. Technology
- targeted platforms and its current state
    - Windows/MINGW(port completed)
    - Windows/MSC(port completed)
    - Linux(port completed)
    - MacOSX(port completed)
    - FreeBSD(port completed)
    - NetBSD(port completed)
    - OpenBSD(port completed)
    - Haiku(port completed)
    - Android(port pending)
    - iOS(port pending)

# 5. Links
- A-GUI - How to build, see [README-BuildingHowTo.md](./README-BuildingHowTo.md)
- The Mindty Kollektiv [Discord Server](https://discord.gg/tMqrmcp23Q)

# 6. Collaboration
- Interested in collaboration? Then drop me a line via mail or use the issues section on [a-gui@github](https://github.com/andreasdr/a-gui/issues)

# 7. Donation 
- I have to pay my bills, beer and stuff, so if you have any use for this open source project, like educational, productive or fun, ..., consider a donation here [PayPal](https://www.paypal.me/andreasdrewke), here [GitHub Sponsors](https://github.com/sponsors/andreasdr) or via [Amazon Wishlist](https://www.amazon.de/hz/wishlist/ls/250IBUL4JSZVR?ref_=wl_share)
