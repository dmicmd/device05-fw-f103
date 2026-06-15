# V-MODEL-TRACEABILITY.md

## Система клавиатуры v1.0

---

# 1. Общая концепция

Данный документ описывает полную прослеживаемость требований системы клавиатуры по V-model:

- SRS (функциональные требования)
- HRS (аппаратные требования)
- PDS (протокол)
- Реализация (модули прошивки)
- Тестирование (unit / integration / system)

---

# 2. V-model структура

```
          SRS / HRS
              ↓
     Архитектурное проектирование
              ↓
        Спецификация протокола (PDS)
              ↓
          Реализация (firmware)
              ↓
        Модульные и интеграционные тесты
              ↓
        Системные и приемочные тесты
```

---

# 3. Матрица трассируемости (функциональные требования)

---

## 3.1 Обработка клавиш

|REQ ID|Требование|Аппаратная часть|Протокол|Модуль|Тест|
|---|---|---|---|---|---|
|REQ-FR-001|обработка нажатий клавиш|GPIO|KEY FRAME|key_matrix.c|test_key_matrix|
|REQ-FR-002|единая клавиатура|GPIO|PANEL+HOST|key_matrix.c|test_merge|
|REQ-FR-003|32 клавиши|GPIO|KEY/PANEL|key_matrix.c|test_matrix|
|REQ-FR-004|антидребезг 20 мс|GPIO/Timer|KEY FRAME|debounce.c|test_debounce|
|REQ-FR-005|состояния клавиш|GPIO|KEY FRAME|key_state.c|test_state|

---

## 3.2 USB HID

|REQ ID|Требование|Аппаратная часть|Протокол|Модуль|Тест|
|---|---|---|---|---|---|
|REQ-FR-010|USB HID устройство|USB D+/D-|HID map|usb_hid.c|test_usb_init|
|REQ-FR-011|только события клавиш|USB|KEY FRAME|usb_hid.c|test_usb_events|
|REQ-FR-012|управление USB|PA1|0xEC/0xED|usb_control.c|test_usb|

---

## 3.3 UART Host

|REQ ID|Требование|Аппаратная часть|Протокол|Модуль|Тест|
|---|---|---|---|---|---|
|REQ-FR-020|UART управление|PA9/PA10|HOST FRAME|uart_host.c|test_uart|
|REQ-FR-021|яркость|TIM1|0xD0–0xDF|brightness.c|test_brightness|
|REQ-FR-022|USB control|PA1|0xEC/0xED|usb_control.c|test_usb_ctrl|
|REQ-FR-023|подсветка клавиш|GPIO/PWM|KEY FRAME|backlight.c|test_led|
|REQ-FR-024|передача клавиш|UART TX|KEY FRAME|uart_tx.c|test_tx|
|REQ-FR-025|heartbeat|UART TX|0x1F|uart_host.c|test_hb|

---

## 3.4 Панели (UART1/2)

|REQ ID|Требование|Аппаратная часть|Протокол|Модуль|Тест|
|---|---|---|---|---|---|
|REQ-FR-030|2 панели|UART2/3|PANEL FRAME|panel.c|test_panel|
|REQ-FR-031|прием клавиш|UART RX|PANEL FRAME|panel_rx.c|test_rx|
|REQ-FR-032|маршрутизация|UART logic|PANEL→HOST|router.c|test_route|
|REQ-FR-033|независимость панелей|UART|PANEL FRAME|panel_mgr.c|test_iso|

---

## 3.5 Подсветка

|REQ ID|Требование|Аппаратная часть|Протокол|Модуль|Тест|
|---|---|---|---|---|---|
|REQ-FR-040|подсветка клавиш|GPIO/PWM|KEY FRAME|backlight.c|test_backlight|
|REQ-FR-041|глобальная яркость|TIM1|BRIGHTNESS|brightness.c|test_global|

---

# 4. Нефункциональные требования

---

## 4.1 Производительность

|REQ ID|Требование|Проверка|
|---|---|---|
|REQ-NFR-001|задержка USB < 10 мс|system test|
|REQ-NFR-002|UART < 5 мс|benchmark|

---

## 4.2 Надежность

|REQ ID|Требование|Проверка|
|---|---|---|
|REQ-NFR-010|игнор некорректных данных|fuzz test|
|REQ-NFR-011|восстановление UART|stress test|

---

## 4.3 Архитектура

|REQ ID|Требование|Проверка|
|---|---|---|
|REQ-NFR-020|слоистая архитектура|code review|
|REQ-NFR-021|разделение HW и логики|static analysis|

---

## 4.4 Сборка и CI

|REQ ID|Требование|Проверка|
|---|---|---|
|REQ-NFR-030|CI сборка|GitLab CI|
|REQ-NFR-031|Docker build|pipeline|
|REQ-NFR-032|unit tests|test runner|

---

## 4.5 Безопасное состояние

|REQ ID|Требование|Проверка|
|---|---|---|
|REQ-NFR-040|безопасный старт|boot test|

---

# 5. Трассировка к протоколу (PDS)

---

## 5.1 Клавиши

|Функция|REQ|Протокол|
|---|---|---|
|нажатие клавиши|REQ-FR-001|KEY FRAME|
|отпускание|REQ-FR-001|KEY FRAME|
|удержание|REQ-FR-005|KEY FRAME|
|панели|REQ-FR-031|PANEL FRAME|

---

## 5.2 Управление

|Функция|REQ|Протокол|
|---|---|---|
|яркость|REQ-FR-021|0xD0–0xDF|
|USB включение|REQ-FR-022|0xED|
|USB выключение|REQ-FR-022|0xEC|

---

# 6. Трассировка к аппаратуре (HRS)

---

## 6.1 GPIO

|Функция|REQ|Пин|
|---|---|---|
|матрица клавиш|REQ-FR-001|PBx/PCx|
|подсветка|REQ-FR-040|PA8|
|USB D+|REQ-FR-010|PA12|
|USB D-|REQ-FR-010|PA11|
|UART Host|REQ-FR-020|PA9/PA10|

---

## 6.2 Временные параметры

|Требование|Аппаратная реализация|
|---|---|
|антидребезг 20 мс|таймер + GPIO|
|удержание 200 мс|SysTick|
|heartbeat 1 с|scheduler|

---

# 7. Стратегия тестирования

---

## 7.1 Уровни тестирования

|Уровень|Описание|
|---|---|
|модульные|функции (матрица, протокол)|
|интеграционные|UART + USB + панели|
|системные|поведение клавиатуры|
|приемочные|работа с хостом|

---

## 7.2 Требования к покрытию

Каждое требование должно иметь:

- реализацию
- минимум 1 модульный тест
- минимум 1 интеграционный тест

---

# 8. Правила V-model

## 8.1 Обязательные условия

- нет требования без теста
- нет модуля без требования
- PDS является источником истины для байтового уровня

---

## 8.2 Источник истины

- SRS — поведение
- HRS — железо
- PDS — протокол
- TRACEABILITY — связующий слой