![LOGO](https://raw.githubusercontent.com/andreasdr/tdme2/master/resources/github/tdme2-logo.png)

This is a documentation of supported TDME2-GUI XML elements and their attributes. This document is WIP.

# 1. Primitive nodes

## 1.1 Node base attributes
| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| id                                | The unique node id within screen                                                       | auto generated id |
| flow                              | floating \| integrated                                                                 | integrated        |
| horizontal-align                  | left \| center \| right                                                                | left              |
| vertical-align                    | top \| center \| bottom                                                                | top               |
| x                                 | x position of node in %, pixel                                             | none              |
| y                                 | y position of node in %, pixel                                                         | none              |
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

## 1.2. \<element\>
| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| disabled                          | true \| false                                                                          | false             |
| focusable                         | true \| false                                                                          | false             |
| ignore-events                     | true \| false                                                                          | false             |
| name                              | formular name of this element                                                          |                   |
| on-initialize                     | SimpleScript expression to be executed initially                                       | none              |
| on-mouse-click                    | SimpleScript expression to be executed if a mouse click did happen                     | none              |
| on-mouse-doubleclick              | SimpleScript expression to be executed if a double mouse click did happen              | none              |
| on-mouse-over                     | SimpleScript expression to be executed if a mouse over event did happen                | none              |
| on-mouse-out                      | SimpleScript expression to be executed if a mouse out event did happen                 | none              |
| on-change                         | SimpleScript expression to be executed if element forwarded a change event             | none              |
| options                           | options in format: "optionName0=optionValue0,...optionNameN=optionValueN               | none              |
| overflow-x                        | hidden \| downsize-children \| scroll                                                  | hidden            |
| overflow-y                        | hidden \| downsize-children \| scroll                                                  | hidden            |
| value                             | value of this element                                                                  |                   |

## 1.3. \<gradient\>
| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| colors                            | percentAt0%=color1,..,percentAtN%=colorN; e.g. 0%=red,50%=green,100%=blue              | none              |
| rotation                          | rotation angle                                                                         | 0.0f              |


## 1.4. Frame Buffer / Image / Texture nodes

### 1.4.1. \<frame-buffer\>
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


### 1.4.2. \<image\>
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

### 1.4.3. \<texture\>
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

    
## 1.5. \<layer\>
| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| overflow-x                        | hidden \| downsize-children \| scroll                                                  | hidden            |
| overflow-y                        | hidden \| downsize-children \| scroll                                                  | hidden            |

## 1.6. \<layout\>
| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| alignment                         | none \| horizontal \| vertical                                                         | none              |
| overflow-x                        | hidden \| downsize-children \| scroll                                                  | hidden            |
| overflow-y                        | hidden \| downsize-children \| scroll                                                  | hidden            |


## 1.7. \<panel\>
| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| alignment                         | none \| horizontal \| vertical                                                         | none              |
| overflow-x                        | hidden \| downsize-children \| scroll                                                  | hidden            |
| overflow-y                        | hidden \| downsize-children \| scroll                                                  | hidden            |

## 1.8. \<space\>

## 1.9 Table nodes

### 1.9.1 \<table\>

### 1.9.2 \<table-row\>

### 1.9.3 \<table-cell\>
| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| alignment                         | none \| horizontal \| vertical                                                         | none              |

## 1.10. Text nodes

### 1.10.1. \<text\>
| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| color                             | text rendering color in html hex notation or color name                                | none              |
| font                              | font location                                                                          | none              |
| text                              | text to be rendered                                                                    | none              |

### 1.10.2. \<styled-text\>
| Attribute name                    | Attribute description                                                                  | Default           |
| --------------------------------- | ---------------------------------------------------------------------------------------| ----------------- |
| color                             | text rendering default color in hex notation or color name                             | none              |
| font                              | text rendering default font location                                                   | none              |
| preformatted                      | preformatted, means preserve new lines and white spaces                                | false             |

The <styled-text>Inner Data</styled-text> is the text that will be rendered. Also note that this element supports some sort of BBCode syntax.

Currently supported BBCode like tags:
  [font=font-location.fnt]Text[/font]
  [color=#ff0000ff|red]Colored Text[/color]
  [url=http://mindty.com/]Text with Link[/url]
  [image]image-location.png[/image]

# 2. Compound elements

## 2.1. \<button\>
        background-image
        disabled
        height
        hide-on
        id
        image
        name
        on-change
        on-initialize
        on-mouse-click
        on-mouse-doubleclick
        on-mouse-out
        on-mouse-over
        show-on
        template
        text
        value
        width

## 2.2. \<checkbox\>
        disabled
        height
        id
        image-checked
        image-unchecked
        name
        on-change
        on-initialize
        on-mouse-click
        on-mouse-doubleclick
        on-mouse-out
        on-mouse-over
        selected
        size
        text
        value
        width

## 2.3.1. Context Menu

### 2.3.1. \<context-menu\>
        * accepts XML within tag
        disabled
        id
        name
        on-change
        on-initialize
        on-mouse-click
        on-mouse-doubleclick
        on-mouse-out
        on-mouse-over

### 2.3.2. \<context-menu-item\>
        * accepts XML within tag
        disabled
        id
        image
        on-change
        on-initialize
        on-mouse-click
        on-mouse-doubleclick
        on-mouse-out
        on-mouse-over
        shortcut
        text
        value

## 2.3. dropdown

### 2.3.1. \<dropdown\>
        * accepts XML within tag
        disabled
        height
        id
        image
        name
        on-change
        on-initialize
        on-mouse-click
        on-mouse-doubleclick
        on-mouse-out
        on-mouse-over
        padding
        template
        text
        width

### 2.3.2. \<dropdown-option\>
        * accepts XML within tag
        disabled
        id
        on-change
        on-initialize
        on-mouse-click
        on-mouse-doubleclick
        on-mouse-out
        on-mouse-over
        selected
        text
        value

## 2.4. \<image-button\>
        disabled
        height
        id
        name
        on-change
        on-initialize
        on-mouse-click
        on-mouse-doubleclick
        on-mouse-out
        on-mouse-over
        src-clicked
        src-disabled
        src-normal
        src-over
        value
        width

## 2.5. \<input\>
        disabled
        height
        hide-on
        hint
        id
        image
        maxlength
        name
        on-change
        on-initialize
        on-mouse-click
        on-mouse-doubleclick
        on-mouse-out
        on-mouse-over
        options
        show-on
        text
        unit
        width

## 2.6. Menu

### 2.6.1. \<menu-header\>
        * accepts XML within tag

### 2.6.2. \<menu-header-item\>
        * accepts XML within tag
        disabled
        id
        name
        on-change
        on-initialize
        on-mouse-click
        on-mouse-doubleclick
        on-mouse-out
        on-mouse-over
        text

### 2.6.3. \<menu-item\>
        * accepts XML within tag
        disabled
        id
        image
        on-change
        on-initialize
        on-mouse-click
        on-mouse-doubleclick
        on-mouse-out
        on-mouse-over
        shortcut
        text
        value

### 2.6.4. \<menu-separator\>

## 2.7. \<progress-bar\>
        id
        name
        show-on
        text-on
        value
        width

## 2.8. \<radiobutton\>
        disabled
        height
        id
        image
        name
        on-change
        on-initialize
        on-mouse-click
        on-mouse-doubleclick
        on-mouse-out
        on-mouse-over
        selected
        template
        text
        value
        width

## 2.9. \<scrollarea\>
        * accepts XML within tag
        alignment
        background-color
        border
        focusable
        height
        hide-on
        horizontal-align
        id
        padding
        show-on
        vertical-align
        width

## 2.10. selectbox

### 2.10.1. \<selectbox\>
        * accepts XML within tag
        boder
        disabled
        height
        id
        name
        on-change
        on-initialize
        on-mouse-click
        on-mouse-doubleclick
        on-mouse-out
        on-mouse-over
        options
        width

### 2.10.2. \<selectbox-option\>
        disabled
        id
        image
        on-change
        on-initialize
        on-mouse-click
        on-mouse-doubleclick
        on-mouse-out
        on-mouse-over
        parent-id
        selected
        text
        value

## 2.11. Sliders

### 2.11.1. \<slider-horizontal\>
        id
        name
        on-change
        value
        width

### 2.11.2. \<slider-vertical\>
        height
        id
        name
        on-change
        template
        value

## 2.12. \<styled-input\>
        * accepts XML within tag
        color
        disabled
        font
        height
        hide-on
        id
        on-change
        on-initialize
        on-mouse-click
        on-mouse-doubleclick
        on-mouse-out
        on-mouse-over
        options
        padding
        preformatted
        show-on
        width

## 2.13. tab

### 2.13.1. \<tab\>
        closeable
        disabled
        id
        image
        on-change
        on-initialize
        on-mouse-click
        on-mouse-doubleclick
        on-mouse-out
        on-mouse-over
        text
        type-color
        value

### 2.13.2. \<tab-content\>
        * accepts XML within tag
        alignment
        horizontal-align
        tab-id
        vertical-align

### 2.13.3. \<tabs\>
        * accepts XML within tag
        alignment
        height
        id
        ignore-events
        width

### 2.13.4. \<tabs-content\>
        * accepts XML within tag
        id
        ignore-events

### 2.13.5. \<tabs-header\>
        * accepts XML within tag
        id
        on-initialize
        scrollable

## 2.14. \<template\>
        id
        name
        src
        type

