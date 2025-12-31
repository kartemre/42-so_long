# so_long - 42 İstanbul Projesi 🎮

**So Long And Thanks For All The Fish!**

Karakterin tüm koleksiyonları toplayıp çıkışa ulaştığı basit 2D oyun.

![42](https://img.shields.io/badge/42-Project-blue)
![Language](https://img.shields.io/badge/Language-C-green)
![Graphics](https://img.shields.io/badge/Graphics-MiniLibX-red)
![Norm](https://img.shields.io/badge/Norm-v4-success)

## 📋 Proje Hakkında

**so_long**, 42 'nin grafik projesidir. Oyuncu haritadaki tüm koleksiyonları toplayıp çıkışa ulaşmalıdır.

### Oyun Kuralları
- Tüm koleksiyonları topla (C)
- Çıkışı bul (E)
- Duvarlardan kaçın (1)
- Boş alanlarda hareket et (0)
- Oyuncu pozisyonundan başla (P)

### Özellikler
- ✅ 42 Norm v4 uyumlu
- ✅ Modüler kod yapısı (14 kaynak dosya)
- ✅ DFS algoritması ile path validation
- ✅ Bellek yönetimi ve hata kontrolü
- ✅ MiniLibX ile grafik rendering

## 🎮 Kontroller

| Tuş | Aksiyon |
|-----|---------|
| `W` veya `↑` | Yukarı |
| `A` veya `←` | Sola |
| `S` veya `↓` | Aşağı |
| `D` veya `→` | Sağa |
| `ESC` | Çıkış |

## 📁 Proje Yapısı

```
42-so_long/
├── inc/                    # Header dosyaları
│   └── so_long.h          # Ana header
├── src/                    # Kaynak kodlar
│   ├── main.c             # Program giriş noktası
│   ├── map_parse.c        # Harita okuma
│   ├── map_parse_utils.c  # Parse yardımcıları
│   ├── map_validate.c     # Harita validasyon
│   ├── map_validate_utils.c
│   ├── map_walls.c        # Duvar kontrolü
│   ├── path_check.c       # DFS path validation
│   ├── path_check_utils.c
│   ├── game.c             # Oyun render
│   ├── game_utils.c
│   ├── game_init.c        # Texture loading
│   ├── game_events.c      # Event handling
│   ├── game_hooks.c
│   └── utils.c            # Genel yardımcılar
├── maps/                   # Test haritaları
│   ├── valid/             # Geçerli haritalar
│   └── error/             # Hata test haritaları
├── textures/              # XPM sprite dosyaları
├── Makefile
└── README.md
```

## 🛠️ Kurulum

### Gereksinimler
- GCC derleyici
- Make
- X11 kütüphaneleri (Linux)
- MiniLibX

### Linux/Ubuntu Kurulumu

```bash
# Bağımlılıkları yükle
sudo apt-get update
sudo apt-get install gcc make libx11-dev libxext-dev libbsd-dev

# Projeyi klonla
git clone <repo-url> so_long
cd so_long

# Derle
make

# Temizle
make clean    # .o dosyalarını sil
make fclean   # Tümünü sil
make re       # Yeniden derle
```

## 🚀 Kullanım

```bash
# Harita dosyası ile çalıştır
./so_long maps/valid/ok.ber

# Geçerli harita ile test
./so_long maps/valid/ok1.ber

# Norm kontrolü
norminette inc/*.h src/*.c
```

## 🗺️ Harita Formatı

Haritalar `.ber` uzantılı ve şu kurallara uymalıdır:

### Geçerli Karakterler
- `0` - Boş alan
- `1` - Duvar
- `C` - Koleksiyon (toplanabilir)
- `E` - Çıkış
- `P` - Oyuncu başlangıç pozisyonu

### Harita Gereksinimleri
✅ Dikdörtgen olmalı  
✅ Duvarlarla (`1`) çevrili olmalı  
✅ Tam olarak 1 oyuncu (`P`) içermeli  
✅ Tam olarak 1 çıkış (`E`) içermeli  
✅ En az 1 koleksiyon (`C`) içermeli  
✅ Tüm koleksiyonlara ve çıkışa ulaşılabilir olmalı  

### Örnek Harita

```
1111111111111
10010000000C1
1000011111001
1P0011E000001
1111111111111
```

## 🎯 Algoritma ve Teknikler

### Path Validation (DFS)
- Depth-First Search ile tüm koleksiyonlara ulaşılabilirlik kontrolü
- Grid kopyalama ve ziyaret edilenler işaretleme
- Recursive DFS implementasyonu

### Bellek Yönetimi
- Dinamik allocation ile harita parsing
- Hata durumlarında proper cleanup
- Leak-free implementation

### Validasyon Katmanları
1. **File Check**: .ber uzantı kontrolü
2. **Parse**: Dosyadan harita okuma
3. **Rectangle**: Dikdörtgen kontrolü
4. **Charset**: Geçerli karakter kontrolü
5. **Count**: P, E, C sayıları kontrolü
6. **Walls**: Duvar çevresi kontrolü
7. **Path**: DFS ile erişilebilirlik kontrolü

## 📊 Norm Uyumu

Proje **42 Norm v4** kurallarına tam uyumludur:

- ✅ Maksimum 25 satır/fonksiyon
- ✅ Maksimum 5 fonksiyon/dosya
- ✅ Maksimum 4 parametre/fonksiyon
- ✅ Tab indentation
- ✅ 80 karakter satır limiti
- ✅ For loop yasağı (while kullanımı)
- ✅ Ternary operator yasağı

```bash
# Tüm dosyalar için norm kontrolü
norminette inc/*.h src/*.c

# Sonuç: Tüm dosyalar OK!
```

## 🧪 Test

### Geçerli Haritalar
```bash
./so_long maps/valid/ok.ber
./so_long maps/valid/ok1.ber
./so_long maps/valid/ok10.ber
```

### Hata Haritaları (Error mesajı vermeli)
```bash
./so_long maps/error/invalidchar.ber    # Geçersiz karakter
./so_long maps/error/not_rect.ber       # Dikdörtgen değil
./so_long maps/error/bad_e.ber          # Exit sayısı hatalı
./so_long maps/error/tiny.ber           # Koleksiyon yok
```

## 🛡️ Hata Yönetimi

Proje şu hataları kontrol eder:

- ❌ Yanlış argüman sayısı
- ❌ .ber olmayan dosya uzantısı
- ❌ Açılamayan dosya
- ❌ Boş veya geçersiz harita
- ❌ Dikdörtgen olmayan harita
- ❌ Geçersiz karakterler
- ❌ Yanlış P, E, C sayıları
- ❌ Duvar eksikliği
- ❌ Erişilemeyen koleksiyonlar

## 📚 Dosya ve Fonksiyon Özeti

### Ana Dosyalar
- **main.c** (5 fonk): Program başlangıç, argüman kontrolü
- **map_parse.c** (4 fonk): Harita dosyası okuma ve parsing
- **map_validate.c** (5 fonk): Harita validasyon
- **map_walls.c** (3 fonk): Duvar kontrolü
- **path_check.c** (3 fonk): DFS path validation
- **game.c** (4 fonk): Rendering ve game loop
- **game_init.c** (5 fonk): MLX ve texture initialization
- **game_events.c** (5 fonk): Klavye ve window event handling

### Yardımcı Dosyalar
- **map_parse_utils.c**: ft_malloc, count_lines, copy_line
- **map_validate_utils.c**: check_rectangle, is_valid_char
- **path_check_utils.c**: dup_grid, free_grid, find_player
- **game_utils.c**: put_tile, get_tile_for_char
- **game_hooks.c**: on_destroy, on_expose
- **utils.c**: error_exit, ft_putstr_fd, ft_putnbr_fd

## 🏗️ Makefile Hedefleri

| Hedef | Açıklama |
|-------|----------|
| `make` | Projeyi derle |
| `make clean` | Object dosyalarını sil |
| `make fclean` | Tümünü temizle |
| `make re` | Yeniden derle |

## 💡 Teknik Detaylar

### Kullanılan Struct'lar
```c
t_map       // Harita verisi (grid, rows, cols)
t_counts    // Element sayıları (C, E, P)
t_game      // Oyun durumu (MLX, textures, player pos)
t_img       // Texture verisi (img pointer, size, bpp)
t_pt        // Koordinat (row, col)
t_reach     // DFS sonuç (reachable C, E)
t_dfs_ctx   // DFS context (grid, dimensions)
t_parse     // Parse helper (grid, first_len)
t_read      // File read helper (buffer, capacity)
```

### Derleme Bayrakları
```bash
-Wall -Wextra -Werror    # Tüm uyarılar aktif
-Iinc                    # Header include path
-I./minilibx-linux       # MLX include path
```

## 🎓 Öğrenilenler

- ✅ Grafik kütüphanesi (MiniLibX) kullanımı
- ✅ Event handling (klavye, mouse, window)
- ✅ Depth-First Search (DFS) algoritması
- ✅ Bellek yönetimi ve leak prevention
- ✅ Modüler kod organizasyonu
- ✅ 42 Norm kurallarına uyum
- ✅ Makefile optimization

## 🚀 Performans

- **Executable boyutu**: ~91KB
- **Kaynak kod satırı**: ~1200 satır
- **Derleme süresi**: <2 saniye
- **Bellek kullanımı**: Minimal (dinamik allocation)

## 📞 İletişim

**ekart** - 42 İstanbul Öğrencisi

## 📜 Lisans

Bu proje 42 School müfredatının bir parçasıdır.

---

⭐ **Not**: 125/100  
🎯 **Durum**: Tamamlandı  
📅 **Tarih**: Aralık 2025


Example:
```bash
./so_long maps/valid/ok.ber
```

## Controls
- **W / ↑** - Move up
- **A / ←** - Move left
- **S / ↓** - Move down
- **D / →** - Move right
- **ESC** - Exit game

## Map Format
Maps are `.ber` files containing:
- `0` - Empty space
- `1` - Wall
- `C` - Collectible
- `E` - Exit
- `P` - Player starting position

### Map Rules
1. Map must be rectangular
2. Map must be surrounded by walls (`1`)
3. Must contain exactly 1 exit (`E`)
4. Must contain exactly 1 starting position (`P`)
5. Must contain at least 1 collectible (`C`)
6. All collectibles and exit must be reachable from starting position

### Example Map
```
1111111111111
10010000000C1
1000011111001
1P0011E000001
1111111111111
```

## Project Structure
```
.
├── Makefile              # Build configuration
├── so_long.h            # Header file
├── step1_main.c         # Main program and validation
├── step2_map.c          # Map loading
├── step3_validate.c     # Map validation (format, counts)
├── step4_walls.c        # Wall validation
├── step5_path.c         # Path finding (DFS)
├── step6_mlx.c          # Graphics and game loop
├── maps/
│   ├── valid/          # Valid test maps
│   └── error/          # Invalid test maps
└── textures/           # Game sprites (XPM format)
```

## Testing

### Valid maps
```bash
./so_long maps/valid/ok.ber
```

### Error handling tests
```bash
# No exit
./so_long maps/error/no_exit.ber

# Not rectangular
./so_long maps/error/no_rectangular.ber

# No valid path
./so_long maps/error/no_valid_road.ber

# Bad extension
./so_long maps/error/badextension1.txt
```

## Makefile Targets
- `make` or `make all` - Compile the project
- `make clean` - Remove object files
- `make fclean` - Remove object files and executable
- `make re` - Recompile from scratch

## 42 School Requirements
This project follows the 42 School norm and includes:
- Strict error handling with "Error\n" messages
- Memory leak prevention
- Norminette compliance
- Proper Makefile with required targets
- No global variables
- Use of authorized functions only

## Author
ekart - 42 Istanbul

## License
This is a 42 School project. Feel free to use for learning purposes.