```csharp
using System.Collections.Concurrent;
using System.Diagnostics;
using System.Threading.Tasks;

// ...

ConcurrentQueue<string> imageQueue = new ConcurrentQueue<string>();

// 이미지 파일 경로를 큐에 추가
imageQueue.Enqueue("image1.jpg");
imageQueue.Enqueue("image2.jpg");
// ...

Parallel.ForEach(imageQueue, imageFile =>
{
    string outputFile = "resized_" + imageFile;
    string ffmpegCommand = $"-i {imageFile} -vf scale=800:600 {outputFile}";

    ProcessStartInfo startInfo = new ProcessStartInfo
    {
        FileName = "ffmpeg",
        Arguments = ffmpegCommand,
        RedirectStandardOutput = true,
        RedirectStandardError = true,
        UseShellExecute = false,
        CreateNoWindow = true
    };

    using (Process process = Process.Start(startInfo))
    {
        process.WaitForExit();
    }
});
```
