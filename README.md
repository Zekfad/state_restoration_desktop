# State restoration for Flutter Desktop

> [!NOTE]
> (WIP) Currently only Windows is supported.

Implements a very basic [`flutter/restoration`](https://api.flutter.dev/flutter/services/SystemChannels/restoration-constant.html)
method channel for Flutter Desktop. This channel is used by [RestorationManager](https://api.flutter.dev/flutter/services/RestorationManager-class.html)
to read and write restoration data.

> [!CAUTION]
> This is not production ready. Data is stored in `restoration.bin` file in the
> app working directory as-is without any compression/encryption.
