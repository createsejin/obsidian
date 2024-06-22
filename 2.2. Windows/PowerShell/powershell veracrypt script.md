```powershell
$veracrypt = "C:\Program Files\VeraCrypt\VeraCrypt.exe"
$work_dir = "G:\내 드라이브\1.창고\정보\Packs"
$pack009 = "Pack009_2024-01-02_001.hc"
$f_key_file = "M:\Keyfiles\diskF"
$p_key_file = "M:\Keyfiles\diskP02"
$s_key_file = "M:\Keyfiles\diskS"
$q_key_file = "M:\PnQ Key.txt"
$kee_file = "M:\session3.txt"

function help_msg {
  'pack m           : mount key capsule readonly mode'
  'pack m rw        : mount key capsule read and write mode'
  'pack m f         : mount F disk'
  'pack m p         : mount P disk'
  'pack m s         : mount S disk'
  'pack m q         : copy Q disk passwd to clipboard'
  'pack k           : copy KeePass passwd to clipboard'
  'pack c           : clear clipboard'
  'pack d           : dismount key capsule'
  'pack d f         : dismount F disk'
  'pack d p         : dismount P disk'
  'pack d s         : dismount S disk'
  'pack d q         : lock Q disk'
}

if ($args[0] -ieq "m") {
  if ($args[1] -ieq "f") {
    if (-not (Test-Path $f_key_file)) {
      'Please mount key capsule first'
    } else {
      Start-Process -FilePath "$veracrypt" -Wait -NoNewWindow `
        -ArgumentList "/quit /silent /auto /v \Device\Harddisk0\Partition2 /letter F /keyfile $f_key_file /tryemptypass /cache no"
    }
  } elseif ($args[1] -ieq "p") {
    if (-not (Test-Path $p_key_file)) {
      'Please mount key capsule first'
    } else {
      Start-Process -FilePath "$veracrypt" -Wait -NoNewWindow `
        -ArgumentList "/quit /silent /auto /v \Device\Harddisk1\Partition2 /letter P /keyfile $p_key_file /tryemptypass /cache no"
    }
  } elseif ($args[1] -ieq "s") {
    if (-not (Test-Path $s_key_file)) {
      'Please mount key capsule first'
    } else {
      Start-Process -FilePath "$veracrypt" -Wait -NoNewWindow `
        -ArgumentList "/quit /silent /auto /v \Device\Harddisk2\Partition2 /letter S /keyfile $s_key_file /tryemptypass /cache no"
    }
  } elseif ($args[1] -ieq "q") {
    if (Test-Path -Path $q_key_file) {
      Get-Content $q_key_file | Select-Object -Index 3 | Set-Clipboard
      "The Q disk password is copied."
      "You should clean up the clipboard after using this: Use `"pack c`"."
    } else {
      'Please mount key capsule first'
    }
  } elseif ($args[1] -ieq "rw") {
    Start-Process -FilePath "$veracrypt" -Wait -NoNewWindow -WorkingDirectory $work_dir `
      -ArgumentList "/quit /auto /volume $pack009 /letter M /m rm /protectMemory /cache no"
  } else {
    Start-Process -FilePath "$veracrypt" -Wait -NoNewWindow -WorkingDirectory $work_dir `
      -ArgumentList "/quit /auto /volume $pack009 /letter M /mountoption ro /m rm /protectMemory /cache no" 
  }
} elseif ($args[0] -ieq "d") {
  if ($args[1] -ieq "f") {
    if (-not (Test-Path "F:\")) {
      'The F disk is not mounted.'
    } else {
      Start-Process -FilePath "$veracrypt" -Wait -NoNewWindow -ArgumentList "/q /s /d F" 
    }
  } elseif ($args[1] -ieq "p") {
    if (-not (Test-Path "P:\")) {
      'The P disk is not mounted.'
    } else {
      Start-Process -FilePath "$veracrypt" -Wait -NoNewWindow -ArgumentList "/q /s /d P" 
    }
  } elseif ($args[1] -ieq "s") {
    if (-not (Test-Path "S:\")) {
      'The S disk is not mounted.'
    } else {
      Start-Process -FilePath "$veracrypt" -Wait -NoNewWindow -ArgumentList "/q /s /d S" 
    }
  } elseif ($args[1] -ieq "q") {
    if (-not (Test-Path "Q:\")) {
      'The Q disk is already locked.'
    } else {
      manage-bde -lock Q:
    }
  } else {
    if (-not (Test-Path "M:\")) {
      'The key capsule is not mounted.'
    } else {
      Start-Process -FilePath "$veracrypt" -Wait -NoNewWindow -ArgumentList "/q /s /d M"
    }
  }
} elseif ($args[0] -ieq "c") {
  Set-Clipboard -Value $null
  "clipboard cleared."
} elseif ($args[0] -ieq "k") {
  if (Test-Path $kee_file) {
    Get-Content $kee_file | Select-Object -Index 0 | Set-Clipboard
    "The KeePass password is copied."
    "You should clean up the clipboard after using this: Use `"pack c`""
  } else {
    'Please mount key capsule first'
  }
} elseif (($args[0] -ieq "--help") -or ($args[0] -ieq "-h") -or ($args[0] -ieq "h") -or ($args[0] -ieq "help")) {
  help_msg
} else {
  help_msg
}
```
