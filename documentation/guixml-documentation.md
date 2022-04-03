![LOGO](https://raw.githubusercontent.com/andreasdr/tdme2/master/resources/github/tdme2-logo.png)

This is a documentation of supported TDME2-GUI XML elements and their attributes. This document is WIP.

# 1. Primitive nodes

# 1.1 Node base attributes
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
| focusable                         | true \| false                                                                          | false             |
| ignore-events                     | true \| false                                                                          | false             |
| on-mouse-click                    | SimpleScript expression to be executed if a mouse click did happen                     | none              |
| options                           | options in format: "optionName0=optionValue0,...optionNameN=optionValueN               | none              |
| overflow-x                        | hidden \| downsize-children \| scroll                                                  | hidden            |
| overflow-y                        | hidden \| downsize-children \| scroll                                                  | hidden            |

## 1.3. \<gradient\>

TODO

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

TODO

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
| color                             | font location                                                                          | none              |
| font                              | font location                                                                          | none              |
| text                              | text to be rendered                                                                    | none              |
| preformatted                      | preformatted, means preserve new lines and white spaces                                | false             |

# 2. Compound elements

## 2.1. \<button\>
        background-image
        disabled
        height
        hide-on
        id
        image
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
        on-mouse-click
        on-mouse-doubleclick
        selected
        size
        text
        value
        width

## 2.3 \<context-menu\>
        * accepts XML within tag
        disabled
        id
        name
        on-change
        on-mouse-click
        on-mouse-doubleclick

## 2.3. dropdown

### 2.3.1. \<dropdown\>
        * accepts XML within tag
        disabled
        height
        id
        image
        on-change
        on-mouse-click
        on-mouse-doubleclick
        padding
        template
        text
        width

### 2.3.2. \<dropdown-option\>
        * accepts XML within tag
        disabled
        id
        on-mouse-click
        on-mouse-doubleclick
        selected
        text
        value

## 2.4. \<input\>
        disabled
        height
        hide-on
        hint
        id
        image
        maxlength
        name
        on-change
        on-mouse-click
        on-mouse-doubleclick
        options
        show-on
        text
        unit
        width

## 2.5. menu

### 2.5.1. \<menu-header\>
        * accepts XML within tag

### 2.5.2. \<menu-header-item\>
        * accepts XML within tag
        disabled
        id
        name
        on-change
        on-mouse-click
        on-mouse-doubleclick
        text

### 2.5.3. \<menu-item\>
        * accepts XML within tag
        disabled
        id
        image
        on-mouse-click
        on-mouse-doubleclick
        shortcut
        text
        value

### 2.5.4. \<menu-separator\>

## 2.6. \<progress-bar\>
        id
        show-on
        text-on
        value
        width

## 2.7. \<radiobutton\>
        disabled
        height
        id
        image
        name
        on-change
        on-mouse-click
        on-mouse-doubleclick
        selected
        template
        text
        value
        width

## 2.8. \<scrollarea\>
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

## 2.9. selectbox

### 2.9.1. \<selectbox\>
        * accepts XML within tag
        boder
        disabled
        height
        id
        name
        on-change
        on-mouse-click
        on-mouse-doubleclick
        options
        width

### 2.9.2. \<selectbox-option\>
        disabled
        id
        image
        on-mouse-click
        on-mouse-doubleclick
        parent-id
        selected
        text
        value

## 2.10. \<slider-vertical\>
        height
        id
        template
        value

## 2.11. \<styled-input\>
        * accepts XML within tag
        color
        disabled
        font
        height
        hide-on
        id
        on-change
        on-mouse-click
        on-mouse-doubleclick
        options
        padding
        preformatted
        show-on
        width

## 2.12. tab

### 2.12.1. \<tab\>
        closeable
        disabled
        id
        image
        on-mouse-click
        on-mouse-doubleclick
        text
        type-color
        value

### 2.12.2. \<tab-content\>
        * accepts XML within tag
        alignment
        horizontal-align
        tab-id
        vertical-align

### 2.12.3. \<tabs\>
        * accepts XML within tag
        alignment
        height
        id
        ignore-events
        width

### 2.12.4. \<tabs-content\>
        * accepts XML within tag
        id
        ignore-events

### 2.12.5. \<tabs-header\>
        * accepts XML within tag
        id
        scrollable

## 2.13. \<template\>
        id
        name
        src
        type

