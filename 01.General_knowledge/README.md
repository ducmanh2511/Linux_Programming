# Hello Library

Thực hành Makefile, static linking và dynamic linking bằng một thư viện C đơn giản.

## 1. Viết thư viện

Tạo `include/hello.h` khai báo hàm:

```c
void hello(void);
```

Trong `src/hello.c`, định nghĩa hàm này để in:

```text
Hello,I am Le Duc Manh!
```

## 2. Viết chương trình chính

Tạo `src/main.c`, include `hello.h` và gọi `hello()` một lần trong `main()`.

## 3. Viết Makefile

Từ cùng mã nguồn, tạo hai thư viện và hai chương trình:

| Thư viện | Chương trình sử dụng |
| --- | --- |
| `libhello.a` — thư viện tĩnh | `app_static` |
| `libhello.so` — thư viện động | `app_dynamic` |

Makefile chỉ cần hỗ trợ:

```bash
make          # Tạo cả hai thư viện và hai chương trình
make clean    # Xóa obj/, lib/ và app/
```

Giữ mã nguồn, header và sản phẩm build trong các thư mục riêng:

```text
hello_library/
├── README.md
├── Makefile
├── include/
│   └── hello.h
├── src/
│   ├── hello.c
│   └── main.c
├── obj/
│   ├── main.o
│   ├── hello.o
│   └── hello_pic.o
├── lib/
│   ├── libhello.a
│   └── libhello.so
└── app/
    ├── app_static
    └── app_dynamic
```

| Thư mục | Nội dung |
| --- | --- |
| `include/` | Header khai báo hàm của thư viện |
| `src/` | Mã nguồn C |
| `obj/` | Object file `.o` |
| `lib/` | Thư viện tĩnh `.a` và thư viện động `.so` |
| `app/` | File thực thi |

Makefile tự tạo `obj/`, `lib/`, `app/`. Các thư mục này nằm trong thư mục dự án, không phải đường dẫn tuyệt đối ở gốc hệ thống.

Chạy các lệnh bên dưới từ thư mục gốc `hello_library/`.


## 4. Chạy thử

Tại thư mục dự án:

```bash
make
./app/app_static
LD_LIBRARY_PATH="$PWD/lib" ./app/app_dynamic
```

Cả hai phải in ra:

```text
Hello, I am Le Duc Manh!
```

`LD_LIBRARY_PATH="$PWD/lib"` giúp bản động tìm thư viện trong `lib/` lúc chạy.

