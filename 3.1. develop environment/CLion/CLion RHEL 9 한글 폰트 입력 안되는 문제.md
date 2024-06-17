This issue might be related to the input method framework (IMF) that CLion uses. CLion uses XIM (X Input Method) by default, which might not work well with some IMFs like IBus. 

You can try to switch the input method to IBus in CLion by setting the `XMODIFIERS` environment variable. Here's how you can do it:

1. Open the `clion.sh` file in the bin directory of your CLion installation. The path might look something like `/path/to/clion/bin/clion.sh`.

2. Add the following line at the beginning of the file:

```bash
export XMODIFIERS=@im=ibus
```

3. Save the file and start CLion using this script.

This will set the input method to IBus when you start CLion. If this doesn't solve your problem, it might be a bug in CLion or in your input method, and you should report it to the JetBrains or IBus support.