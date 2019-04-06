 $(document).ready(function(){
	   $(window).bind('scroll', function() {
	   var navHeight = $( window ).height() - 70;
			 if ($(window).scrollTop() > 500) {
				 $('nav').addClass('fixed');
			 }
			 else {
				 $('nav').removeClass('fixed');
			 }
		});
	});

window.onresize = function(event) {
    if(event.currentTarget.outerWidth < 1026){
        document.getElementById("hidden-jumbotron-as-sm").style.display = "none";
     
}

$(window).
(function() {
  if($(this).scrollTop() != 0) {
    $('#to-top').fadeIn(); 
  } else {
    $('#to-top').fadeOut();
  }
});

$('#to-top').click(function() {
  $('body,html').animate({scrollTop:0},"fast");
});
    

var num = 250; //number of pixels before modifying styles

$(window).bind('scroll', function () {
    if ($(window).scrollTop() > num) {
        $('.main-menu').addClass('fixed');
    } else {
        $('.main-menu').removeClass('fixed');
    }
});

    jQuery("document").ready(function($){
	
	var nav = $('.main-menu');
	
	$(window).scroll(function () {
		if ($(this).scrollTop() > 136) {
			nav.addClass("fixed");
		} else {
			nav.removeClass("fixed");
		}
	});
 
});

