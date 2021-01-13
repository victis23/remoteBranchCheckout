#!/bin/bash

# make -C /Users/scottleonard/Downloads/Coding/BashScripts/gitCheckoutScript/gitCheckout/gitCheckout/ 
# Could also have done the above using:
(cd /${HOME}/Downl*/Co*/BashScripts/gitCheckoutScript/gitCheckout/gitCheckout && make)

sleep 1; sudo mv /Users/scottleonard/Downloads/Coding/BashScripts/gitCheckoutScript/gitCheckout/gitCheckout/gitmaster /usr/local/bin/gitmaster
