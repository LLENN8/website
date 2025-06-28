# Documentation

Hi, welcome! This documentation is mostly for myself so I don’t forget how it works or how to run/deploy it.

---

## Project Folder Structure

```
website/
├── CMakeLists.txt          # Build config
├── docs/                   # This documentation and related info
├── include/                # Header files (*.h)
├── post/                   # Blog posts written in Markdown
├── resources/              # Fonts, images, and style.css
├── src/                    # Main C++ sources (Wt + logic)
│   ├── about.cpp           # About page
│   ├── blog.cpp            # Blog index page
│   ├── footer.cpp          # Footer widget
│   ├── index.cpp           # Entry point
│   ├── mdreader.cpp        # Markdown reader (with YAML frontmatter)
│   ├── navbar.cpp          # Navbar component
│   └── rss.cpp             # RSS generator
├── generate_rss.cpp        # Standalone RSS generator tool
```

---

## Dependencies

* [**Wt (Web Toolkit)**](https://www.webtoolkit.eu/wt) - C++ web framework
* [**cmark**](https://github.com/commonmark/cmark) - Markdown to HTML converter (used for rendering `.md` posts)
* [**clang**](https://clang.llvm.org/) - C/C++ Compiler
* [**cmake**](https://cmake.org/) - C++ Build System


---

## Building and Running

### 1. Dependencies:

Install Clang, Wt, cmake, and cmark on system:

```bash
sudo apt install libcmark-dev cmake clang
```
for WT, You should compile and install wt manually:

[**How to install WT**](https://www.webtoolkit.eu/wt/doc/reference/html/InstallationUnix.html) - Official Docs WT

[**How to install WT**](https://misaka.bearblog.dev/wt-web-framework-untuk-cpp) - My Blog post

### 2. Build the app:

```bash
cd website
mkdir build && cd build
cmake ..
make
```
### 3. symlink resources and posts to build folder, so app can use it:
in build folder:

```bash
    ln -s ../resources ./resources
    ln -s ../posts ./posts
```

### 3. Run:

you can change the port if you want
```bash
./index --docroot . --http-address=0.0.0.0 --http-port=8080
```

if you experience error like these when running ./index:
```
[info] "WServer/wthttp: fatal: Error reading: /etc/wt/wt_config.xml: <debug-level>: expecting 'script' or 'all'"
```
just go to:
```
sudo nano /etc/wt/wt_config.xml
```
then search debug-level tag and delete that
```
  <debug-level>script</debug-level>  -> delete this
  ```
  the error itself from wt

### regenerate rss:
```bash
./rss
```

---

## Note

This project uses:

* **SPA-like architecture**: Only one main page, with routes handled internally via `Wt::WApplication::setInternalPath()`.
* **Markdown posts**:

  * Supports frontmatter via `--- key: value ---` blocks.
  * Parsed using `std::regex`.
* **RSS support**:

  * Static RSS generator (`generate_rss.cpp`).
  * Output: `rss.xml`, generated manually after adding a new `.md` post.

---

## How to Create a New Post

1. Create a Markdown file in the `post/` folder. For example: `post/post_1.md`

```md
---
title: My First Post
description: My first post about the blog 
date: June 23, 2025
---

# Hello World

This is my first post!
```
To render properly on the blog page, each post must include a title, description, and date.

Regenerate RSS after adding post:
going to build folder then

```bash
./rss
```