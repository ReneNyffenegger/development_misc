# css.html

[css.html](https://raw.github.com/ReneNyffenegger/development_misc/master/web/js/jquery/css.html) sets 
[css properties](https://github.com/ReneNyffenegger/development_misc/tree/master/web/css/properties#readme) with `.css()`.

# ready.html

The arguably most basic jquery script:
```javascript   
$(document).ready(function(){
    alert('Ready');
});
```

[ready.html](https://raw.github.com/ReneNyffenegger/development_misc/master/web/js/jquery/ready.html)

# mousemove.html

Uses the `mousemove` event to track the coordinates of the mouse

[mousemove.html](https://raw.github.com/ReneNyffenegger/development_misc/master/web/js/jquery/mousemove.html)

Further Keywords: e.pageX, e.pageY

#selector_01.html

Demonstrates `$('#div_id')` to select a `<div>` via its *id*.

Further Keywords: addClass

[selector_01.html](https://raw.github.com/ReneNyffenegger/development_misc/master/web/js/jquery/selector_01.html)

#selector_02.html

Demonstrates `$('p')` to select all `<p>`s

Further keywords: addClass

[selector_02.html](https://raw.github.com/ReneNyffenegger/development_misc/master/web/js/jquery/selector_02.html)

#click_01.html

Uses `$('a')` to select *all* `<a>` and applies `click()` to add (or *bind*) a *click handler*.

Further keywords: text(), this

[click_01.html](https://raw.github.com/ReneNyffenegger/development_misc/master/web/js/jquery/click_01.html)

#add_remove_class_01.html

Uses `addClass` and `removeClass` to change the appearance of a `<div>`.

Further keywords: click().

[add_remove_class_01.html](https://raw.github.com/ReneNyffenegger/development_misc/master/web/js/jquery/add_remove_class_01.html)

#hide_show.html

Uses `hide()` to hide a `<div>` and `show()` to show it again.

Further keywords: click()

[hide_show.html](https://raw.github.com/ReneNyffenegger/development_misc/master/web/js/jquery/hide_show.html)

#val.html

[val.html](https://raw.github.com/ReneNyffenegger/development_misc/master/web/js/jquery/val.html) demonstrates [.val()](http://api.jquery.com/val/) in order to get the values of `<input>` elements.

#append_01.html

[append_01.html](https://raw.github.com/ReneNyffenegger/development_misc/master/web/js/jquery/append_01.html) demonstrates [.append()](http://api.jquery.com/append/): the function `createGrid` accepts the three parameters `numberOfRows`, `numberOfColumns` and `cellLength` and creates an according grid in the `<div id='container'></div>`.
