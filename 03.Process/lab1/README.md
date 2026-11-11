# Lab 1: Quan sát zombie process

## 1. Mục tiêu

- Phân biệt PID c?a process cha và con.
- Quan sát trạng thái Sleeping (`S`) và Zombie (`Z`).
- Đọc thông tin process bằng `ps` và `/proc`.
- Hiểu vai trò của `waitpid()` trong việc thu hồi process con.

## 2. Chương trình thí nghiệm

File `zombie.c`:

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        printf("[Con] PID = %d, kết thúc ngay\n", getpid());
        exit(42);
    }

    printf("[Cha] PID = %d, PID con = %d\n", getpid(), pid);
    printf("[Cha] Không gọi wait(), ngủ 60 giây\n");

    sleep(60);
    return 0;
}
```

## 3. Biên dịch và chạy

Thực hiện trong terminal Linux:

```bash
gcc -Wall -Wextra zombie.c -o zombie
./zombie &
```

Dấu `&` giúp chương trình chạy nền để có thể nhập lệnh quan sát
trong cùng terminal.

Ví dụ đầu ra:

```text
[Cha] PID = 5000, PID con = 5001
[Cha] Không gọi wait(), ngủ 60 giây
[Con] PID = 5001, kết thúc ngay
```

PID và thứ tự các dòng in có thể khác giữa các lần chạy.

## 4. Quan sát trong 60 giây

### Cách 1: Dùng ps

```bash
ps aux | grep zombie
```

Hoặc xem đúng hai process:

```bash
ps -o pid,ppid,stat,comm -p 5000,5001
```

Thay `5000,5001` bằng PID cha và con của lần chạy hiện tại.

Kết quả minh họa:

```text
  PID  PPID STAT COMMAND
 5000  4000 S    zombie
 5001  5000 Z    zombie
```

Cột `STAT` có thể kèm ký tự phụ; chú ý ký tự `S` và `Z`.

| Process | Trạng thái | Giải thích |
|---|---|---|
| Cha | S | Đang chờ hết thời gian sleep |
| Con | Z | Đã kết thúc, cha chưa gọi wait/waitpid để thu hồi |

Lưu ý: `grep zombie` lọc theo chữ `zombie`, không lọc theo trạng thái.
Nó có thể hiện cả cha, con và chính lệnh grep.

### Cách 2: Đọc /proc

```bash
cat /proc/5001/status | grep -E "Name|Pid|PPid|State"
```

Thay `5001` bằng PID con thực tế.

Các dòng chính cần quan sát:

```text
Name:   zombie
State:  Z (zombie)
Pid:    5001
PPid:   5000
```

`/proc/<PID>/status` cung cấp thông tin về process có PID tương ứng.

## 5. Quan sát sau 60 giây

Chạy lại các lệnh quan sát:

```bash
ps -o pid,ppid,stat,comm -p 5000,5001
cat /proc/5001/status
```

Kết quả mong đợi sau khi hệ thống thu hồi con:

- Không còn hai process trong kết quả ps.
- Lệnh cat báo `No such file or directory`.

Giải thích:

1. Cha hết sleep và kết thúc bằng `return 0`.
2. Con zombie được chuyển cho process nhận nuôi.
3. Process nhận nuôi thu hồi con, nên thông tin trong /proc biến mất.

Zombie không tự hết hạn sau 60 giây; 60 giây là thời gian cha
còn sống trong chương trình này.

## 6. Thêm waitpid() và so sánh

Thêm thư viện:

```c
#include <sys/wait.h>
```

Trong nhánh cha, đặt đoạn sau trước `sleep(60)`:

```c
int status;

if (waitpid(pid, &status, 0) == -1) {
    perror("waitpid");
    return 1;
}

if (WIFEXITED(status)) {
    printf("[Cha] Exit code của con: %d\n", WEXITSTATUS(status));
}

sleep(60);
```

Biên dịch và chạy lại, ghi nhận PID mới rồi quan sát.

Kết quả mong đợi:

- Cha in exit code của con là `42`.
- Trong lúc cha ngủ, con đã được thu hồi nên không còn dòng zombie.

| Trường hợp | Trong lúc cha ngủ |
|---|---|
| Không gọi waitpid() | Con còn ở trạng thái Z |
| Gọi waitpid() trước sleep() | Con đã được thu hồi |

## 7. Kết luận

- fork() tạo process con có PID riêng.
- Con kết thúc nhưng chưa được cha thu hồi sẽ trở thành zombie.
- sleep() giữ cha sống để có thời gian quan sát.
- waitpid() đọc trạng thái kết thúc và thu hồi process con.
