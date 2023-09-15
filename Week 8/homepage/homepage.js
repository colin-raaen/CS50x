 //Let forms load first before checking
 document.addEventListener('DOMContentLoaded', function()
 {
    // Get the current URL
    let currentUrl = window.location.href;
    // Get all the links in the navigation bar
    let links = document.querySelectorAll('.topnav a');

    // Loop through each link and compare its URL to the current URL
    for (let link of links)
    {
        // If the link URL matches the current URL, add a class to the link
        if (link.href === currentUrl)
        {
            link.classList.add("current");
        }
    }

    /* Toggle between showing and hiding the navigation menu links when the user clicks on the hamburger menu / bar icon */
    function myFunction() {
    var x = document.getElementById("myTopnav");
      if (x.style.display === "block") {
        x.style.display = "none";
      } else {
          x.style.display = "block";
      }
  }
 });