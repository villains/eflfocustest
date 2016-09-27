# eflfocustest

The purpose of this test program is to explain the problem I'm having with getting keystroke
event callbacks to run for non-interactive widgets.

The overall structure:

- win
  - mainBox
    - topBar (where app status stuff will go, placeholder label for now)
    - flip (main content area)
      - content1
      - content2
      
## What is supposed to happen

Press the 'f' key to flip between content1 and content2.

The contentKeyDownCallback1() function should run for key
down events, while content1 is visible in the flip. However that does not happen.

While content1 is visible, you should be able to press 'g' to flip to content2.

## Acknowledgements

The user okra on IRC channel #edevelop helpfully pointed to some code in the ephoto app,
file ephoto_single_browser.c lines 2195-2203. The code in createContent1() is modelled after that.
