
	function toggle_visibility(id) {
       var e = document.getElementById(id);
       if(e.style.display == 'block')
          e.style.display = 'none';
       else
          e.style.display = 'block';
    }
	
	function on_off_VAULT(id,obj_id){
       var checkBox = document.getElementById(id);
       var e = document.getElementById(obj_id);
	   if (checkBox.checked == true)
          e.style.display = 'block';
	   else
		  e.style.display = 'none';
	}
