![LOGO](https://raw.githubusercontent.com/andreasdr/tdme2/master/resources/github/tdme2-logo.png)

This is the documentation of supported TDME2-GUI XML elements and their attributes. This document is WIP (It misses effects, some more descriptions and maybe even some graphical presentation and for sure examples).

# 1. Primitive nodes

## 1.1 Node base attributes

| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| id                                | the unique node id within screen                                                       | auto generated id |
| flow                              | floating \| integrated                                                                 | integrated        |
| horizontal-align                  | left \| center \| right                                                                | left              |
| vertical-align                    | top \| center \| bottom                                                                | top               |
| left                              | x position of node in %, pixel                                                         | none              |
| top                               | y position of node in %, pixel                                                         | none              |
| width                             | width in %, pixel or rest(*) or auto for computed width                                | auto              |
| height                            | height in %, pixel or rest(*) or auto for computed height                              | auto              |
| factor                            |                                                                                        | 0                 |
| background-color                  | background color in html hex notation or color name                                    | transparent       |
| background-image                  | background image location                                                              | none              |
| background-image-scale9           | background image scale 9 in pixels for left, top, right, bottom area                   | 0 pixel           |
| background-image-scale9-left      | background image scale 9 in pixels for left area                                       | 0 pixel           |
| background-image-scale9-top       | background image scale 9 in pixels for top area                                        | 0 pixel           |
| background-image-scale9-right     | background image scale 9 in pixels for right area                                      | 0 pixel           |
| background-image-scale9-bottom    | background image scale 9 in pixels for bottom area                                     | 0 pixel           |
| background-image-effect-color-mul | background image color multiplication in hex notation or color name                    | #ffffffff         |
| background-image-effect-color-add | background image color addition in hex notation or color name                          | #00000000         |
| border                            | border in pixels for left, top, right, bottom area                                     | 0 pixel           |
| border-left                       | border in pixels for left area                                                         | 0 pixel           |
| border-top                        | border in pixels for top area                                                          | 0 pixel           |
| border-right                      | border in pixels for right area                                                        | 0 pixel           |
| border-bottom                     | border in pixels for bottom area                                                       | 0 pixel           |
| border-color                      | border color in html hex notation or color name for left, top, right, bottom area      | transparent       |
| border-color-left                 | border color in html hex notation or color name for left area                          | transparent       |
| border-color-top                  | border color in html hex notation or color name for top area                           | transparent       |
| border-color-right                | border color in html hex notation or color name for right area                         | transparent       |
| border-color-bottom               | border color in html hex notation or color name for bottom area                        | transparent       |
| padding                           | padding in pixels for left, top, right, bottom area                                    | 0 pixel           |
| padding-left                      | padding in pixels for left area                                                        | 0 pixel           |
| padding-top                       | padding in pixels for top area                                                         | 0 pixel           |
| padding-right                     | padding in pixels for right area                                                       | 0 pixel           |
| padding-bottom                    | padding in pixels for bottom area                                                      | 0 pixel           |
| show-on                           | comma separated list for conditions that has to be met (or connection) to show node    | none              |
| hide-on                           | comma separated list for conditions that has to be met (or connection) to hide node    | none              |

## 1.2. \<screen\> node

| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| alignment                         | none \| horizontal \| vertical                                                         | none              |
| overflow-x                        | hidden \| downsize-children \| scroll                                                  | hidden            |
| overflow-y                        | hidden \| downsize-children \| scroll                                                  | hidden            |
| scrollable                        | true \| false                                                                          | false             |
| popup                             | true \| false                                                                          | false             |
| min-width                         | minimal supported screen width, if screen width < min-width, the screen gets scaled    | none              |
| min-height                        | minimal supported screen height, if screen height < min-height, the screen gets scaled | none              |
| max-width                         | maximal supported screen width, if screen width > max-width, the screen gets scaled    | none              |
| max-height                        | maximal supported screen height, if screen width > max-height, the screen gets scaled  | none              |

This element supports all other elements as sub elements.

## 1.3. \<element\> node

| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| disabled                          | true \| false                                                                          | false             |
| focusable                         | true \| false                                                                          | false             |
| ignore-events                     | true \| false                                                                          | false             |
| on-initialize                     | SimpleScript expression to be executed initially                                       | none              |
| on-mouse-click                    | SimpleScript expression to be executed if a mouse click did happen                     | none              |
| on-mouse-doubleclick              | SimpleScript expression to be executed if a double mouse click did happen              | none              |
| on-mouse-over                     | SimpleScript expression to be executed if a mouse over event did happen                | none              |
| on-mouse-out                      | SimpleScript expression to be executed if a mouse out event did happen                 | none              |
| on-change                         | SimpleScript expression to be executed if element forwarded a change event             | none              |
| options                           | options in format: "optionName0=optionValue0,...optionNameN=optionValueN               | none              |
| overflow-x                        | hidden \| downsize-children \| scroll                                                  | hidden            |
| overflow-y                        | hidden \| downsize-children \| scroll                                                  | hidden            |
| name                              | formular name of this element                                                          |                   |
| value                             | value of this element                                                                  |                   |

This element supports all other elements as sub elements.

## 1.4. \<gradient\> node

| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| colors                            | percentAt0%=color1,..,percentAtN%=colorN; e.g. 0%=red,50%=green,100%=blue              | none              |
| rotation                          | rotation angle                                                                         | 0.0f              |


## 1.5. Frame Buffer / Image / Texture / Video nodes

### 1.5.1. \<frame-buffer\> node

| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| clipping                          | frame buffer clipping in pixels for left, top, right, bottom area                      | 0 pixel           |
| clipping-left                     | frame buffer clipping in pixels for left area                                          | 0 pixel           |
| clipping-top                      | frame buffer clipping in pixels for top area                                           | 0 pixel           |
| clipping-right                    | frame buffer clipping in pixels for right area                                         | 0 pixel           |
| clipping-right                    | frame buffer clipping in pixels for bottom area                                        | 0 pixel           |
| mask                              | frame buffer mask image location                                                       | none              |
| mask-max-value                    | mask max value, means if mask image pixel > mask max value the fragment is discared    | none              |
| scale9                            | frame buffer scale 9 in pixels for left, top, right, bottom area                       | 0 pixel           |
| scale9-left                       | frame buffer scale 9 in pixels for left area                                           | 0 pixel           |
| scale9-top                        | frame buffer scale 9 in pixels for top area                                            | 0 pixel           |
| scale9-right                      | frame buffer scale 9 in pixels for right area                                          | 0 pixel           |
| scale9-bottom                     | frame buffer scale 9 in pixels for bottom area                                         | 0 pixel           |
| effect-color-mul                  | frame buffer color multiplication in hex notation or color name                        | #ffffffff         |
| effect-color-add                  | frame buffer color addition in hex notation or color name                              | #00000000         |
| horizontal-scale                  | float factor to scale original frame buffer width with                                 | 1.0               |
| vertical-scale                    | float factor to scale original frame buffer width with                                 | 1.0               |
| mirror-x                          | mirror frame buffer on x axis                                                          | false             |
| mirror-y                          | mirror frame buffer on y axis                                                          | false             |


### 1.5.2. \<image\> node

| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| clipping                          | image clipping in pixels for left, top, right, bottom area                             | 0 pixel           |
| clipping-left                     | image clipping in pixels for left area                                                 | 0 pixel           |
| clipping-top                      | image clipping in pixels for top area                                                  | 0 pixel           |
| clipping-right                    | image clipping in pixels for right area                                                | 0 pixel           |
| clipping-right                    | image clipping in pixels for bottom area                                               | 0 pixel           |
| mask                              | image mask image location                                                              | none              |
| mask-max-value                    | mask max value, means if mask image pixel > mask max value the fragment is discared    | none              |
| scale9                            | image scale 9 in pixels for left, top, right, bottom area                              | 0 pixel           |
| scale9-left                       | image scale 9 in pixels for left area                                                  | 0 pixel           |
| scale9-top                        | image scale 9 in pixels for top area                                                   | 0 pixel           |
| scale9-right                      | image scale 9 in pixels for right area                                                 | 0 pixel           |
| scale9-bottom                     | image scale 9 in pixels for bottom area                                                | 0 pixel           |
| effect-color-mul                  | image color multiplication in hex notation or color name                               | #ffffffff         |
| effect-color-add                  | image color addition in hex notation or color name                                     | #00000000         |
| horizontal-scale                  | float factor to scale original image width with                                        | 1.0               |
| vertical-scale                    | float factor to scale original image width with                                        | 1.0               |
| mirror-x                          | mirror image on x axis                                                                 | false             |
| mirror-y                          | mirror image on y axis                                                                 | false             |
| rotation                          | rotation angle                                                                         | 0.0               |
| src                               | image location                                                                         | 0.0               |

### 1.5.3. \<texture\> node

| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| clipping                          | texture clipping in pixels for left, top, right, bottom area                           | 0 pixel           |
| clipping-left                     | texture clipping in pixels for left area                                               | 0 pixel           |
| clipping-top                      | texture clipping in pixels for top area                                                | 0 pixel           |
| clipping-right                    | texture clipping in pixels for right area                                              | 0 pixel           |
| clipping-right                    | texture clipping in pixels for bottom area                                             | 0 pixel           |
| mask                              | texture mask texture location                                                          | none              |
| mask-max-value                    | mask max value, means if mask texture pixel > mask max value the fragment is discared  | none              |
| scale9                            | texture scale 9 in pixels for left, top, right, bottom area                            | 0 pixel           |
| scale9-left                       | texture scale 9 in pixels for left area                                                | 0 pixel           |
| scale9-top                        | texture scale 9 in pixels for top area                                                 | 0 pixel           |
| scale9-right                      | texture scale 9 in pixels for right area                                               | 0 pixel           |
| scale9-bottom                     | texture scale 9 in pixels for bottom area                                              | 0 pixel           |
| effect-color-mul                  | texture color multiplication in hex notation or color name                             | #ffffffff         |
| effect-color-add                  | texture color addition in hex notation or color name                                   | #00000000         |
| horizontal-scale                  | float factor to scale original texture width with                                      | 1.0               |
| vertical-scale                    | float factor to scale original texture width with                                      | 1.0               |
| mirror-x                          | mirror texture on x axis                                                               | false             |
| mirror-y                          | mirror texture on y axis                                                               | false             |

### 1.5.4. \<video\> node

| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| clipping                          | video clipping in pixels for left, top, right, bottom area                             | 0 pixel           |
| clipping-left                     | video clipping in pixels for left area                                                 | 0 pixel           |
| clipping-top                      | video clipping in pixels for top area                                                  | 0 pixel           |
| clipping-right                    | video clipping in pixels for right area                                                | 0 pixel           |
| clipping-right                    | video clipping in pixels for bottom area                                               | 0 pixel           |
| mask                              | video mask video location                                                              | none              |
| mask-max-value                    | mask max value, means if mask video pixel > mask max value the fragment is discared    | none              |
| scale9                            | video scale 9 in pixels for left, top, right, bottom area                              | 0 pixel           |
| scale9-left                       | video scale 9 in pixels for left area                                                  | 0 pixel           |
| scale9-top                        | video scale 9 in pixels for top area                                                   | 0 pixel           |
| scale9-right                      | video scale 9 in pixels for right area                                                 | 0 pixel           |
| scale9-bottom                     | video scale 9 in pixels for bottom area                                                | 0 pixel           |
| effect-color-mul                  | video color multiplication in hex notation or color name                               | #ffffffff         |
| effect-color-add                  | video color addition in hex notation or color name                                     | #00000000         |
| horizontal-scale                  | float factor to scale original video width with                                        | 1.0               |
| vertical-scale                    | float factor to scale original video width with                                        | 1.0               |
| mirror-x                          | mirror video on x axis                                                                 | false             |
| mirror-y                          | mirror video on y axis                                                                 | false             |
| src                               | video location                                                                         | 0.0               |

## 1.6. \<layer\> node

| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| overflow-x                        | hidden \| downsize-children \| scroll                                                  | hidden            |
| overflow-y                        | hidden \| downsize-children \| scroll                                                  | hidden            |

This element supports all other elements as sub elements.

## 1.7. \<layout\> node

| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| alignment                         | none \| horizontal \| vertical                                                         | none              |
| overflow-x                        | hidden \| downsize-children \| scroll                                                  | hidden            |
| overflow-y                        | hidden \| downsize-children \| scroll                                                  | hidden            |

This element supports all other elements as sub elements.

## 1.8. \<panel\> node

| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| alignment                         | none \| horizontal \| vertical                                                         | none              |
| overflow-x                        | hidden \| downsize-children \| scroll                                                  | hidden            |
| overflow-y                        | hidden \| downsize-children \| scroll                                                  | hidden            |

This element supports all other elements as sub elements.

## 1.9. \<space\> node

## 1.10. Table nodes

### 1.10.1. \<table\> node

This element supports \<table-row\> as sub elements.

### 1.10.2. \<table-row\> node

This element supports  \<table-cell\> as sub elements.

### 1.10.3 \<table-cell\> node

| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| alignment                         | none \| horizontal \| vertical                                                         | none              |

This element supports all other elements as sub elements.

## 1.11. Text nodes

### 1.11.1. \<text\> node

| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| color                             | text rendering color in html hex notation or color name                                | none              |
| font                              | TTF font location                                                                      | none              |
| size                              | TTF font size                                                                          | none              |
| text                              | text to be rendered                                                                    | none              |

### 1.11.2. \<styled-text\> node

| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| color                             | text rendering default color in hex notation or color name                             | none              |
| font                              | TTF font location                                                                      | none              |
| size                              | TTF font size                                                                          | none              |
| preformatted                      | preformatted, means preserve new lines and white spaces                                | false             |

The \<styled-text\>Inner Data\<\/styled-text\> is the text that will be rendered. Also note that this element supports some sort of BBCode syntax.

Currently supported BBCode like tags are:
```
[font=font-location.ttf]Text[/font]
[size=size]Sized Text[/size]
[color=#ff0000ff|red]Colored Text[/color]
[url=http://mindty.com/]Text with Link[/url]
[image=horizontal-scale:50%|0.5,vertical-scale:50%|0.5,width:100,height:100,effect-color-mul:#ff0000ff,effect-color-add:#ff000000]image.png[/image]
```

## 1.12. \<template\>

| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| id                                | the unique node id within screen that might be passed to the template XML              | auto generated id |
| src                               | the template XML location                                                              | none              |
| ...                               | other attributes that might be passed to template XML                                  | none              |

# 2. Compound elements

## 2.1. \<button\>

| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| id                                | the unique node id within screen                                                       | auto generated id |
| background-image                  | location of background image                                                           | none              |
| show-on                           | comma separated list for conditions that has to be met (or connection) to show node    | none              |
| hide-on                           | comma separated list for conditions that has to be met (or connection) to hide node    | none              |
| disabled                          | true \| false                                                                          | false             |
| width                             | width in %, pixel or rest(*) or auto for computed width                                | auto              |
| height                            | height in %, pixel or rest(*) or auto for computed height                              | auto              |
| image                             | image location                                                                         | none              |
| text                              | button text                                                                            | none              |
| on-initialize                     | SimpleScript expression to be executed initially                                       | none              |
| on-mouse-click                    | SimpleScript expression to be executed if a mouse click did happen                     | none              |
| on-mouse-doubleclick              | SimpleScript expression to be executed if a double mouse click did happen              | none              |
| on-mouse-over                     | SimpleScript expression to be executed if a mouse over event did happen                | none              |
| on-mouse-out                      | SimpleScript expression to be executed if a mouse out event did happen                 | none              |
| name                              | formular name of this element                                                          | none              |
| value                             | value of this element                                                                  | none              |
| template                          | location of template XML file to override compound element XML                         | none              |

## 2.2. \<checkbox\>

| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| id                                | the unique node id within screen                                                       | auto generated id |
| show-on                           | comma separated list for conditions that has to be met (or connection) to show node    | none              |
| hide-on                           | comma separated list for conditions that has to be met (or connection) to hide node    | none              |
| disabled                          | true \| false                                                                          | false             |
| size                              | checked/unchecked checkbox image width and height                                      | 25 Pixel          |
| image-checked                     | checked checkbox image location                                                        | YES               |
| image-unchecked                   | unchecked checkbox image location                                                      | YES               |
| text                              | text to render related to checkbox representation itself                               | YES               |
| selected                          | true \| false                                                                          | false             |
| on-initialize                     | SimpleScript expression to be executed initially                                       | none              |
| on-mouse-click                    | SimpleScript expression to be executed if a mouse click did happen                     | none              |
| on-mouse-doubleclick              | SimpleScript expression to be executed if a double mouse click did happen              | none              |
| on-mouse-over                     | SimpleScript expression to be executed if a mouse over event did happen                | none              |
| on-mouse-out                      | SimpleScript expression to be executed if a mouse out event did happen                 | none              |
| on-change                         | SimpleScript expression to be executed if element forwarded a change event             | none              |
| name                              | formular name of this element                                                          | none              |
| value                             | value of this element, which will represent selection state                            | none              |
| template                          | location of template XML file to override compound element XML                         | none              |

## 2.3. Context Menu

### 2.3.1. \<context-menu\>

| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| id                                | the unique node id within screen                                                       | auto generated id |
| show-on                           | comma separated list for conditions that has to be met (or connection) to show node    | none              |
| hide-on                           | comma separated list for conditions that has to be met (or connection) to hide node    | none              |
| disabled                          | true \| false                                                                          | false             |
| on-initialize                     | SimpleScript expression to be executed initially                                       | none              |
| on-mouse-click                    | SimpleScript expression to be executed if a mouse click did happen                     | none              |
| on-mouse-doubleclick              | SimpleScript expression to be executed if a double mouse click did happen              | none              |
| on-mouse-over                     | SimpleScript expression to be executed if a mouse over event did happen                | none              |
| on-mouse-out                      | SimpleScript expression to be executed if a mouse out event did happen                 | none              |
| template                          | location of template XML file to override compound element XML                         | none              |

This element supports \<context-menu-item\> and others as sub elements.

### 2.3.2. \<context-menu-item\>

| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| id                                | the unique node id within screen                                                       | auto generated id |
| show-on                           | comma separated list for conditions that has to be met (or connection) to show node    | none              |
| hide-on                           | comma separated list for conditions that has to be met (or connection) to hide node    | none              |
| disabled                          | true \| false                                                                          | false             |
| image                             | image location                                                                         | none              |
| shortcut                          | context menu shortcut                                                                  | none              |
| text                              | context menu item text                                                                 | none              |
| on-initialize                     | SimpleScript expression to be executed initially                                       | none              |
| on-mouse-click                    | SimpleScript expression to be executed if a mouse click did happen                     | none              |
| on-mouse-doubleclick              | SimpleScript expression to be executed if a double mouse click did happen              | none              |
| on-mouse-over                     | SimpleScript expression to be executed if a mouse over event did happen                | none              |
| on-mouse-out                      | SimpleScript expression to be executed if a mouse out event did happen                 | none              |
| template                          | location of template XML file to override compound element XML                         | none              |

## 2.4. Dropdown

### 2.4.1. \<dropdown\>

| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| id                                | the unique node id within screen                                                       | auto generated id |
| show-on                           | comma separated list for conditions that has to be met (or connection) to show node    | none              |
| hide-on                           | comma separated list for conditions that has to be met (or connection) to hide node    | none              |
| disabled                          | true \| false                                                                          | false             |
| width                             | width in %, pixel or rest(*) or auto for computed width                                | 100%              |
| height                            | height in %, pixel or rest(*) or auto for computed height                              | auto              |
| text                              | initial text to display                                                                | none              |
| padding                           | padding for dropdown options                                                           | 0                 |
| on-initialize                     | SimpleScript expression to be executed initially                                       | none              |
| on-mouse-click                    | SimpleScript expression to be executed if a mouse click did happen                     | none              |
| on-mouse-doubleclick              | SimpleScript expression to be executed if a double mouse click did happen              | none              |
| on-mouse-over                     | SimpleScript expression to be executed if a mouse over event did happen                | none              |
| on-mouse-out                      | SimpleScript expression to be executed if a mouse out event did happen                 | none              |
| on-change                         | SimpleScript expression to be executed if element forwarded a change event             | none              |
| name                              | formular name of this element                                                          | none              |
| value                             | value of this element                                                                  | none              |
| template                          | location of template XML file to override compound element XML                         | none              |

This element supports \<dropdown-option\> and others as sub elements.

### 2.4.2. \<dropdown-option\>

| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| id                                | the unique node id within screen                                                       | auto generated id |
| show-on                           | comma separated list for conditions that has to be met (or connection) to show node    | none              |
| hide-on                           | comma separated list for conditions that has to be met (or connection) to hide node    | none              |
| disabled                          | true \| false                                                                          | false             |
| text                              | option text to display                                                                 | none              |
| selected                          | true \| false                                                                          | false             |
| on-initialize                     | SimpleScript expression to be executed initially                                       | none              |
| on-mouse-click                    | SimpleScript expression to be executed if a mouse click did happen                     | none              |
| on-mouse-doubleclick              | SimpleScript expression to be executed if a double mouse click did happen              | none              |
| on-mouse-over                     | SimpleScript expression to be executed if a mouse over event did happen                | none              |
| on-mouse-out                      | SimpleScript expression to be executed if a mouse out event did happen                 | none              |
| value                             | value of this element, which will represent selection state                            | none              |
| template                          | location of template XML file to override compound element XML                         | none              |

## 2.5. \<image-button\>

| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| id                                | the unique node id within screen                                                       | auto generated id |
| show-on                           | comma separated list for conditions that has to be met (or connection) to show node    | none              |
| hide-on                           | comma separated list for conditions that has to be met (or connection) to hide node    | none              |
| disabled                          | true \| false                                                                          | false             |
| width                             | width in %, pixel or rest(*) or auto for computed width                                | auto              |
| height                            | height in %, pixel or rest(*) or auto for computed height                              | auto              |
| on-initialize                     | SimpleScript expression to be executed initially                                       | none              |
| on-mouse-click                    | SimpleScript expression to be executed if a mouse click did happen                     | none              |
| on-mouse-doubleclick              | SimpleScript expression to be executed if a double mouse click did happen              | none              |
| on-mouse-over                     | SimpleScript expression to be executed if a mouse over event did happen                | none              |
| on-mouse-out                      | SimpleScript expression to be executed if a mouse out event did happen                 | none              |
| src-clicked                       | image location for clicked button state                                                | none              |
| src-disabled                      | image location for disabled button state                                               | none              |
| src-normal                        | image location for normal button state                                                 | none              |
| src-over                          | image location for mouse over button state                                             | none              |
| name                              | formular name of this element                                                          | none              |
| value                             | value of this element, which will represent selection state                            | none              |
| template                          | location of template XML file to override compound element XML                         | none              |

## 2.6. \<input\>

| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| id                                | the unique node id within screen                                                       | auto generated id |
| show-on                           | comma separated list for conditions that has to be met (or connection) to show node    | none              |
| hide-on                           | comma separated list for conditions that has to be met (or connection) to hide node    | none              |
| disabled                          | true \| false                                                                          | false             |
| width                             | width in %, pixel or rest(*) or auto for computed width                                | auto              |
| height                            | height in %, pixel or rest(*) or auto for computed height                              | auto              |
| maxlength                         | max length input restriction                                                           | 0 or no limit     |
| text                              | initial text                                                                           | none              |
| hint                              | text hint to show if no text was entered yet                                           | none              |
| image                             | location of image to display additionally                                              | none              |
| unit                              | unit, e.g. M(eter), S(econds), ...                                                     | none              |
| options                           | type=float\|int,min=xyz,max=xyz,step=xyz,decimals=xyz, e.g. "type=int,min=0,step=1"    | none              |
| on-initialize                     | SimpleScript expression to be executed initially                                       | none              |
| on-mouse-click                    | SimpleScript expression to be executed if a mouse click did happen                     | none              |
| on-mouse-doubleclick              | SimpleScript expression to be executed if a double mouse click did happen              | none              |
| on-mouse-over                     | SimpleScript expression to be executed if a mouse over event did happen                | none              |
| on-mouse-out                      | SimpleScript expression to be executed if a mouse out event did happen                 | none              |
| on-change                         | SimpleScript expression to be executed if element forwarded a change event             | none              |
| name                              | formular name of this element                                                          | none              |
| value                             | value of this element, which will represent selection state                            | none              |

## 2.7. Menu

### 2.7.1. \<menu-header\>

| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| id                                | the unique node id within screen                                                       | auto generated id |
| show-on                           | comma separated list for conditions that has to be met (or connection) to show node    | none              |
| hide-on                           | comma separated list for conditions that has to be met (or connection) to hide node    | none              |

This element supports \<menu-header-item\> and others as sub elements.

### 2.7.2. \<menu-header-item\>

| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| id                                | the unique node id within screen                                                       | auto generated id |
| show-on                           | comma separated list for conditions that has to be met (or connection) to show node    | none              |
| hide-on                           | comma separated list for conditions that has to be met (or connection) to hide node    | none              |
| disabled                          | true \| false                                                                          | false             |
| text                              | item text to display                                                                   | none              |
| on-initialize                     | SimpleScript expression to be executed initially                                       | none              |
| on-mouse-click                    | SimpleScript expression to be executed if a mouse click did happen                     | none              |
| on-mouse-doubleclick              | SimpleScript expression to be executed if a double mouse click did happen              | none              |
| on-mouse-over                     | SimpleScript expression to be executed if a mouse over event did happen                | none              |
| on-mouse-out                      | SimpleScript expression to be executed if a mouse out event did happen                 | none              |
| template                          | location of template XML file to override compound element XML                         | none              |

This element supports \<menu-item\>and others as sub elements.

### 2.7.3. \<menu-item\>

| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| id                                | the unique node id within screen                                                       | auto generated id |
| show-on                           | comma separated list for conditions that has to be met (or connection) to show node    | none              |
| hide-on                           | comma separated list for conditions that has to be met (or connection) to hide node    | none              |
| disabled                          | true \| false                                                                          | false             |
| image                             | menu item image location                                                               | none              |
| shortcut                          | menu item shortcut                                                                     | none              |
| text                              | menu item text                                                                         | none              |
| on-initialize                     | SimpleScript expression to be executed initially                                       | none              |
| on-mouse-click                    | SimpleScript expression to be executed if a mouse click did happen                     | none              |
| on-mouse-doubleclick              | SimpleScript expression to be executed if a double mouse click did happen              | none              |
| on-mouse-over                     | SimpleScript expression to be executed if a mouse over event did happen                | none              |
| on-mouse-out                      | SimpleScript expression to be executed if a mouse out event did happen                 | none              |
| template                          | location of template XML file to override compound element XML                         | none              |

### 2.7.4. \<menu-separator\>

## 2.8. \<moveable\>

| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| id                                | the unique node id within screen                                                       | auto generated id |
| show-on                           | comma separated list for conditions that has to be met (or connection) to show node    | none              |
| hide-on                           | comma separated list for conditions that has to be met (or connection) to hide node    | none              |
| horizontal-align                  | left \| center \| right                                                                | left              |
| vertical-align                    | top \| center \| bottom                                                                | top               |
| alignment                         | none \| horizontal \| vertical                                                         | none              |
| left                              | x position of node in %, pixel                                                         | none              |
| top                               | y position of node in %, pixel                                                         | none              |
| width                             | width in %, pixel or rest(*) or auto for computed width                                | auto              |
| height                            | height in %, pixel or rest(*) or auto for computed height                              | auto              |
| template                          | location of template XML file to override compound element XML                         | none              |

This element supports all other elements as sub elements.

## 2.8. \<progress-bar\>

| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| id                                | the unique node id within screen                                                       | auto generated id |
| show-on                           | comma separated list for conditions that has to be met (or connection) to show node    | none              |
| hide-on                           | comma separated list for conditions that has to be met (or connection) to hide node    | none              |
| text-on                           | true \|false to enable/disable text rendering                                          | false             |
| width                             | width in %, pixel                                                                      | 223               |
| template                          | location of template XML file to override compound element XML                         | none              |

## 2.9. \<radiobutton\>

| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| id                                | the unique node id within screen                                                       | auto generated id |
| show-on                           | comma separated list for conditions that has to be met (or connection) to show node    | none              |
| hide-on                           | comma separated list for conditions that has to be met (or connection) to hide node    | none              |
| disabled                          | true \| false                                                                          | false             |
| image                             | radiobutton image location                                                             | YES               |
| text                              | text to render related to radiobutton representation itself                            | YES               |
| selected                          | true \| false                                                                          | false             |
| on-initialize                     | SimpleScript expression to be executed initially                                       | none              |
| on-mouse-click                    | SimpleScript expression to be executed if a mouse click did happen                     | none              |
| on-mouse-doubleclick              | SimpleScript expression to be executed if a double mouse click did happen              | none              |
| on-mouse-over                     | SimpleScript expression to be executed if a mouse over event did happen                | none              |
| on-mouse-out                      | SimpleScript expression to be executed if a mouse out event did happen                 | none              |
| on-change                         | SimpleScript expression to be executed if element forwarded a change event             | none              |
| name                              | formular name of this element                                                          | none              |
| value                             | value of this element, which will represent selection state                            | none              |
| template                          | location of template XML file to override compound element XML                         | none              |

## 2.10. \<scrollarea\>

| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| id                                | the unique node id within screen                                                       | auto generated id |
| show-on                           | comma separated list for conditions that has to be met (or connection) to show node    | none              |
| hide-on                           | comma separated list for conditions that has to be met (or connection) to hide node    | none              |
| width                             | width in %, pixel or rest(*) or auto for computed width                                | 100%              |
| height                            | height in %, pixel or rest(*) or auto for computed height                              | 100%              |
| background-color                  | background color in html hex notation or color name                                    | transparent       |
| border                            | border in pixels for left, top, right, bottom area                                     | 0 pixel           |
| horizontal-align                  | left \| center \| right                                                                | left              |
| vertical-align                    | top \| center \| bottom                                                                | top               |
| alignment                         | none \| horizontal \| vertical                                                         | none              |
| padding                           | padding for content node                                                               | 0                 |
| template                          | location of template XML file to override compound element XML                         | none              |

## 2.11. Selectbox

### 2.11.1. \<selectbox\>

| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| id                                | the unique node id within screen                                                       | auto generated id |
| show-on                           | comma separated list for conditions that has to be met (or connection) to show node    | none              |
| hide-on                           | comma separated list for conditions that has to be met (or connection) to hide node    | none              |
| disabled                          | true \| false                                                                          | false             |
| width                             | width in %, pixel or rest(*) or auto for computed width                                | 100%              |
| height                            | height in %, pixel or rest(*) or auto for computed height                              | auto              |
| on-initialize                     | SimpleScript expression to be executed initially                                       | none              |
| on-mouse-click                    | SimpleScript expression to be executed if a mouse click did happen                     | none              |
| on-mouse-doubleclick              | SimpleScript expression to be executed if a double mouse click did happen              | none              |
| on-mouse-over                     | SimpleScript expression to be executed if a mouse over event did happen                | none              |
| on-mouse-out                      | SimpleScript expression to be executed if a mouse out event did happen                 | none              |
| on-change                         | SimpleScript expression to be executed if element forwarded a change event             | none              |
| options                           | supports optional multiple selecting by "multiple" option                              | none              |
| name                              | formular name of this element                                                          | none              |
| value                             | value of this element                                                                  | none              |
| template                          | location of template XML file to override compound element XML                         | none              |

This element supports \<selectbox-option\> and others as sub elements.

### 2.11.2. \<selectbox-option\>

| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| id                                | the unique node id within screen                                                       | auto generated id |
| show-on                           | comma separated list for conditions that has to be met (or connection) to show node    | none              |
| hide-on                           | comma separated list for conditions that has to be met (or connection) to hide node    | none              |
| disabled                          | true \| false                                                                          | false             |
| image                             | select box option image location                                                       | none              |
| text                              | text to render                                                                         | none              |
| selected                          | true \| false                                                                          | false             |
| on-initialize                     | SimpleScript expression to be executed initially                                       | none              |
| on-mouse-click                    | SimpleScript expression to be executed if a mouse click did happen                     | none              |
| on-mouse-doubleclick              | SimpleScript expression to be executed if a double mouse click did happen              | none              |
| on-mouse-over                     | SimpleScript expression to be executed if a mouse over event did happen                | none              |
| on-mouse-out                      | SimpleScript expression to be executed if a mouse out event did happen                 | none              |
| parent-id                         | Used to generate hierarchical/tree like select box options                             | none              |
| value                             | value of this element, which will represent selection state                            | none              |
| template                          | location of template XML file to override compound element XML                         | none              |

## 2.12. Horizontal selector

### 2.12.1. \<selector-horizontal\>

| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| id                                | the unique node id within screen                                                       | auto generated id |
| show-on                           | comma separated list for conditions that has to be met (or connection) to show node    | none              |
| hide-on                           | comma separated list for conditions that has to be met (or connection) to hide node    | none              |
| on-initialize                     | SimpleScript expression to be executed initially                                       | none              |
| on-mouse-click                    | SimpleScript expression to be executed if a mouse click did happen                     | none              |
| on-mouse-doubleclick              | SimpleScript expression to be executed if a double mouse click did happen              | none              |
| on-mouse-over                     | SimpleScript expression to be executed if a mouse over event did happen                | none              |
| on-mouse-out                      | SimpleScript expression to be executed if a mouse out event did happen                 | none              |
| name                              | formular name of this element                                                          | none              |
| value                             | value of this element                                                                  | none              |

This element supports  \<selector-horizontal-option\> and others as sub elements.

### 2.12.2. \<selector-horizontal-option\>

| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| id                                | the unique node id within screen                                                       | auto generated id |
| show-on                           | comma separated list for conditions that has to be met (or connection) to show node    | none              |
| hide-on                           | comma separated list for conditions that has to be met (or connection) to hide node    | none              |
| disabled                          | true \| false                                                                          | false             |
| text                              | text to render                                                                         | none              |
| selected                          | true \| false                                                                          | false             |
| on-initialize                     | SimpleScript expression to be executed initially                                       | none              |
| on-mouse-click                    | SimpleScript expression to be executed if a mouse click did happen                     | none              |
| on-mouse-doubleclick              | SimpleScript expression to be executed if a double mouse click did happen              | none              |
| on-mouse-over                     | SimpleScript expression to be executed if a mouse over event did happen                | none              |
| on-mouse-out                      | SimpleScript expression to be executed if a mouse out event did happen                 | none              |
| value                             | value of this element, which will represent selection state                            | none              |

## 2.13. Sliders

### 2.13.1. \<slider-horizontal\>

| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| id                                | the unique node id within screen                                                       | auto generated id |
| show-on                           | comma separated list for conditions that has to be met (or connection) to show node    | none              |
| hide-on                           | comma separated list for conditions that has to be met (or connection) to hide node    | none              |
| disabled                          | true \| false                                                                          | false             |
| width                             | width in %, pixel or rest(*)                                                           | none              |
| on-initialize                     | SimpleScript expression to be executed initially                                       | none              |
| on-mouse-click                    | SimpleScript expression to be executed if a mouse click did happen                     | none              |
| on-mouse-doubleclick              | SimpleScript expression to be executed if a double mouse click did happen              | none              |
| on-mouse-over                     | SimpleScript expression to be executed if a mouse over event did happen                | none              |
| on-mouse-out                      | SimpleScript expression to be executed if a mouse out event did happen                 | none              |
| on-change                         | SimpleScript expression to be executed if element forwarded a change event             | none              |
| name                              | formular name of this element                                                          | none              |
| value                             | value of this element, ranging from 0.0 <= value <= 1.0                                | none              |
| template                          | location of template XML file to override compound element XML                         | none              |

### 2.13.2. \<slider-vertical\>

| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| id                                | the unique node id within screen                                                       | auto generated id |
| show-on                           | comma separated list for conditions that has to be met (or connection) to show node    | none              |
| hide-on                           | comma separated list for conditions that has to be met (or connection) to hide node    | none              |
| disabled                          | true \| false                                                                          | false             |
| height                            | height in %, pixel or rest(*)                                                          | none              |
| on-initialize                     | SimpleScript expression to be executed initially                                       | none              |
| on-mouse-click                    | SimpleScript expression to be executed if a mouse click did happen                     | none              |
| on-mouse-doubleclick              | SimpleScript expression to be executed if a double mouse click did happen              | none              |
| on-mouse-over                     | SimpleScript expression to be executed if a mouse over event did happen                | none              |
| on-mouse-out                      | SimpleScript expression to be executed if a mouse out event did happen                 | none              |
| on-change                         | SimpleScript expression to be executed if element forwarded a change event             | none              |
| name                              | formular name of this element                                                          | none              |
| value                             | value of this element, ranging from 0.0 <= value <= 1.0                                | none              |
| template                          | location of template XML file to override compound element XML                         | none              |

## 2.14. \<styled-input\>

| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| id                                | the unique node id within screen                                                       | auto generated id |
| show-on                           | comma separated list for conditions that has to be met (or connection) to show node    | none              |
| hide-on                           | comma separated list for conditions that has to be met (or connection) to hide node    | none              |
| width                             | width in %, pixel or rest(*) or auto for computed width                                | auto              |
| height                            | height in %, pixel or rest(*) or auto for computed height                              | auto              |
| disabled                          | true \| false                                                                          | false             |
| color                             | text rendering default color in hex notation or color name                             | none              |
| font                              | text rendering default font location                                                   | none              |
| preformatted                      | preformatted, means preserve new lines and white spaces                                | false             |
| on-initialize                     | SimpleScript expression to be executed initially                                       | none              |
| on-mouse-click                    | SimpleScript expression to be executed if a mouse click did happen                     | none              |
| on-mouse-doubleclick              | SimpleScript expression to be executed if a double mouse click did happen              | none              |
| on-mouse-over                     | SimpleScript expression to be executed if a mouse over event did happen                | none              |
| on-mouse-out                      | SimpleScript expression to be executed if a mouse out event did happen                 | none              |
| on-change                         | SimpleScript expression to be executed if element forwarded a change event             | none              |

The \<styled-text\>Inner Data\<\/styled-text\> is the text that will be rendered. Also note that this element supports some sort of BBCode syntax.

Currently supported BBCode like tags are:
```
[font=font-location.ttf]Text[/font]
[size=size]Sized Text[/size]
[color=#ff0000ff|red]Colored Text[/color]
[url=http://mindty.com/]Text with Link[/url]
[image=horizontal-scale:50%|0.5,vertical-scale:50%|0.5,width:100,height:100,effect-color-mul:#ff0000ff,effect-color-add:#ff000000]image.png[/image]
```

## 2.15. Tabs

### 2.15.1. \<tabs\>

| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| id                                | the unique node id within screen                                                       | auto generated id |
| show-on                           | comma separated list for conditions that has to be met (or connection) to show node    | none              |
| hide-on                           | comma separated list for conditions that has to be met (or connection) to hide node    | none              |
| width                             | width in %, pixel or rest(*) or auto for computed width                                | 100%              |
| height                            | height in %, pixel or rest(*) or auto for computed height                              | *                 |
| alignment                         | none \| horizontal \| vertical                                                         | none              |
| ignore-events                     | true \| false                                                                          | false             |

This element supports \<tabs-header\>,  \<tabs-content\> and others as sub elements.

### 2.15.2. \<tabs-header\>

| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| id                                | the unique node id within screen                                                       | auto generated id |
| show-on                           | comma separated list for conditions that has to be met (or connection) to show node    | none              |
| hide-on                           | comma separated list for conditions that has to be met (or connection) to hide node    | none              |
| on-initialize                     | SimpleScript expression to be executed initially                                       | none              |
| scrollable                        | true \| false                                                                          | false             |

This element supports \<tab\> and others as sub elements.

### 2.15.3. \<tab\>

| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| id                                | the unique node id within screen                                                       | auto generated id |
| show-on                           | comma separated list for conditions that has to be met (or connection) to show node    | none              |
| hide-on                           | comma separated list for conditions that has to be met (or connection) to hide node    | none              |
| disabled                          | true \| false                                                                          | false             |
| closable                          | true \| false, which enables the closing icon to appear                                | false             |
| image                             | tab image location                                                                     | none              |
| text                              | tab label text                                                                         | none              |
| type-color                        | tab type color, which is also display in tab header tab                                | transparent       |
| on-initialize                     | SimpleScript expression to be executed initially                                       | none              |
| on-mouse-click                    | SimpleScript expression to be executed if a mouse click did happen                     | none              |
| on-mouse-doubleclick              | SimpleScript expression to be executed if a double mouse click did happen              | none              |
| on-mouse-over                     | SimpleScript expression to be executed if a mouse over event did happen                | none              |
| on-mouse-out                      | SimpleScript expression to be executed if a mouse out event did happen                 | none              |

### 2.15.4. \<tabs-content\>

| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| id                                | the unique node id within screen                                                       | auto generated id |
| show-on                           | comma separated list for conditions that has to be met (or connection) to show node    | none              |
| hide-on                           | comma separated list for conditions that has to be met (or connection) to hide node    | none              |
| ignore-events                     | true \| false                                                                          | false             |

This element supports \<tab-content\> and others as sub elements.

### 2.15.5. \<tab-content\>

| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| id                                | the unique node id within screen                                                       | auto generated id |
| show-on                           | comma separated list for conditions that has to be met (or connection) to show node    | none              |
| hide-on                           | comma separated list for conditions that has to be met (or connection) to hide node    | none              |
| tab-id                            | the unique tab node id within screen which is conntected to this content node          | none              |
| horizontal-align                  | left \| center \| right                                                                | left              |
| vertical-align                    | top \| center \| bottom                                                                | top               |
| alignment                         | none \| horizontal \| vertical                                                         | none              |
        
This element supports all other elements as sub elements.
