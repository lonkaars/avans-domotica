define(`docname',
	ifelse(NAME, `pva', `Plan van aanpak',
	       NAME, `pve', `Pakket van eisen',
	       NAME, `research', `Research document',
				 `UNKNOWN???'))dnl

<!DOCTYPE html>
<html lang="en-US">
<link>
	<meta charset="utf-8">
	<style>undivert(`gen/style.css')</style>
	<script>undivert(`gen/paged.polyfill.js')</script>
	`<script defer>
	window.onload = function() {
		document.querySelectorAll("nav li").forEach(item => {
			var heading = "";
			var parent = item;
			for (parent = item; parent.nodeName != "NAV"; parent = parent.parentNode) {
				if (parent.nodeName != "LI") continue;
				heading = parent.getAttribute("data-item-num") + "." + heading;
			}

			item.setAttribute("heading-num-fix", heading.substr(0, heading.length - 1));
		});
	}
	</script>'
</head>
<body>
	<div class="docintro">
		<span class="left">
			docname()<br/>
			Project Domotica<br/>
			esyscmd(`LANG="en_US.utf8" date "+%B %d, %Y"')
		</span>
		<span class="right">
			Joshua Regnier <b>(2183008)</b><br/>
			Loek Le Blansch <b>(2180996)</b><br/>
			Niels Stunnebrink <b>(2184532)</b>
		</span>
	</div>
	<h1>Table of contents</h1>
	undivert(NAME`.toc')
	undivert(NAME`.con')
</body>
</html>
