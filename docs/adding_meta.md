
# Adding `<meta>` Tags

When you want to add `<meta>` tags (for example, for responsive design), in plain HTML you can simply write:

```html
<meta name="viewport" content="width=device-width, initial-scale=1.0">
````

However, if you are using Wt, you might try using `addMetaHeader()`, but this usually does not work as expected due to the application lifecycle.

## The solution

The recommended solution is to add your meta tags directly in the Wt configuration file. You can add them **globally** or override them per application.

### Global configuration

If you want your application to be responsive, it is better to add the meta tag globally.

Open your configuration file:

```bash
nano /etc/wt/wt_config.xml
```

Scroll up and look for the `<head-matter>` section.

For example, if you want to add a viewport meta tag, you can write:

```xml
<head-matter>
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
</head-matter>
```

> **Note:** You should create a separate `<head-matter>` tag for each meta tag you want to add.

