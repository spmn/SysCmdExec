# SysCmdExec
SA-MP server plugin whose sole purpose is to execute system commands and print the output in server_log and console.

## Native(s):
```PAWN
native SysCmdExec(cmd[]); 

// Example usage:
main()
{
    SysCmdExec("dir");
}
```

## Warning:
* This plugin is not threaded, meaning that executing time-consuming commands could hang your server.
* This software is for educational purposes only. No responsibility is held or accepted for misuse.
