변수
```powershell
$veracrypt = "C:\Program Files\VeraCrypt\VeraCrypt.exe"
$is_active = $false
```

Print Output
```powershell
function help_msg {
  'pack m           : mount key capsule readonly mode'
  'pack m rw        : mount key capsule read and write mode'
  'pack m f         : mount F disk'
```

Function
```powershell
function mount_vera_disk {
  param (
    [string]$letter,
    [string]$key_file,
    [string]$device
  )
  if (-not (Test-Path "M:\")) {
    'Please mount key capsule first'
  }
  elseif (Test-Path "$letter`:\") {
    "$letter disk already mounted."
  }
```

```powershell
function MSTestClassMethodNumberdTest {
  param (
    [Parameter(Mandatory = $true)]
    [int]$class,
    [int]$method
  )
...
```
이 function에서 만약 두번째 매개변수가 입력되지 않으면 `$method`는 0이 된다.

if문 
```powershell
  if (-not (Test-Path "M:\")) {
    'Please mount key capsule first'
  }
  
  if ($args[0] -ieq "m") {
	  if ($args[1] -ieq "f") {
	    mount_vera_disk F $f_key_file $f_device
	  }
	  elseif ($args[1] -ieq "p") {
	    mount_vera_disk P $p_key_file $p_device
	  }
	  elseif ($args[1] -ieq "s") {
	    mount_vera_disk S $s_key_file $s_device
	  }
```

foreach
```powershell
if ($args[0] -ieq "m") {
  if ($args.Count -gt 2) {
    foreach ($arg in $args[1..-1]) {
      if ($arg -ieq "f") {
        mount_vera_disk F $f_key_file $f_device
      }
      elseif ($arg -ieq "p") {
        mount_vera_disk P $p_key_file $p_device
      }
      elseif ($arg -ieq "s") {
        mount_vera_disk S $s_key_file $s_device
      }
      elseif ($arg -ieq "q") {
        QdiskUnlock
      }
    }
  }
```
`$args[1..-1]`은 배열 슬라이싱이다. 마지막에 `-1`은 요소 끝을 의미한다.

