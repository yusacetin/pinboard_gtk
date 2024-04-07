## Deprecation

See https://github.com/yusacetin/pinboard for the new version.

## Pinboard

A GTK 3 program to copy paste from a preconfigured set of texts. Designed to be assigned to a keyboard shortcut such as CTRL + ALT + V. This is a very early build that I put together in about an hour, I plan to implement text based configuation file support in the ~~near~~ future to allow for the customization of the items without editing source code.

## Information

Requires `xclip` to run (as of 6 July 2023, to ensure GTK version agnosticity). Navigation wrapping is disabled in the default configuration but you can enable it by changing the `NAV_WRAP` constant in the first line after the include in the code to `1`. You can use vim keys (hjkl) to navigate.

### License

GNU General Public License v3 or later.