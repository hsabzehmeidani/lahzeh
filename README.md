<div dir="rtl">
بسم الله

# تقویم لحظه

لحظه یک تقویم خط فرمانی هجری (شمسی و قمری) و میلادی (گرگوری) است.

![تقویم لحظه](lahzeh.gif)

## نصب برنامه

### توزیع دبیان/اوبونتو

**۱. نصب بسته‌های پیش‌نیاز**

</div>

```bash
sudo apt install git \
locales locales-all \
make gcc libc6-dev
```

<div dir="rtl">

**۲. دریافت محتوای برنامه**

</div>

```bash
APPSPATH="/opt/applications/"

sudo mkdir -p ${APPSPATH}

sudo chown user:user ${APPSPATH}

cd ${APPSPATH}

git clone https://github.com/hsabzehmeidani/lahzeh.git
```

<div dir="rtl">

**۳. ایجاد پرونده اجرایی برنامه**

در صورتی که از توزیع لینوکس ۶۴بیت استفاده می‌کنید، پرونده اجرایی برنامه در شاخه `bin` موجود است و نیازی به اجرای دستور `INSTALL` نمی‌باشد.

</div>

```bash
${APPSPATH}/lahzeh/INSTALL
```

<div dir="rtl">

در ادامه دستور `ln` را اجرا کنید.

</div>

```bash
sudo ln -s ${APPSPATH}/lahzeh/AppRun /usr/local/bin/lahzeh
```

<div dir="rtl">

**۴. نمایش تقویم در شبیه‌ساز ترمینال:**

</div>

```bash
echo -e "\n# lahzeh calendar\nlahzeh -d -e" >> ~/.bashrc
```

<div dir="rtl">

موفق باشید.

</div>
