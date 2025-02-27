i18next.use(window.i18nextBrowserLanguageDetector);

i18next.init({
	autorun: true,
	debug: isLocalEnvironment(),
	detection: {
		order: ["querystring", "cookie", "navigator"],
		caches: ["cookie"],
		cookieMinutes: 172800 // 120 days
	},
	fallbackLng: ["en"],
	resources: {
		en: {
			translation: TRANSLATION_EN_US
		},
		de: {
			translation: TRANSLATION_DE_DE
		},
		nl: {
			translation: TRANSLATION_NL
		}
	}
}, (error) => {
	if (error) {
		console.error("error while initializing i18next", error);
	}
	initLanguageDropdown(i18next.resolvedLanguage);
	applyLanguageToHtml();
});

i18next.on("languageChanged", applyLanguageToHtml);

function applyLanguageToHtml() {
	document.querySelectorAll("[data-i18next]")
		.forEach((element) => {
			element.innerHTML = i18next.t(element.dataset.i18next);
		});
}

function initLanguageDropdown(language) {

	let languageSelect = document.getElementById("language");

	// The following four lines are a bugfix for Safari on iOS.
	// The state of the currently selected option would not change in the select until you click on
	// it (showing an initial empty select).
	// The workaround clones the complete select, removes it from the DOM and then adds it again. When changing
	// the currently selected option on the clone, the UI updates accordingly even on iOS Safari.
	// Interestingly the problem does not occur with Safari for macOS (or e.g. Firefox for macOS).
	let cloneLanguageSelect = languageSelect.cloneNode(true);
	languageSelect.remove();
	document.getElementById("language-select-container").append(cloneLanguageSelect);
	languageSelect = cloneLanguageSelect;

	// set initial language for the dropdown
	languageSelect.value = language;

	// setup listener for dropdown change
	languageSelect.addEventListener("change", (event) => {
		// Change the "lang" attribute on the HTML element.
		// We need this to get correct hyphenation for the selected language.
		document.getElementsByTagName("html")[0].lang = event.target.value;

		// inform i18next of the change
		i18next.changeLanguage(event.target.value, (error) => {
			if (error) {
				console.error("error while changing language", error);
			}
		});
	});
}
