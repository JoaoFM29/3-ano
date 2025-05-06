$(document).ready(function() {
    $('#toggleBtn').click(function() {
      var passwordField = $('#password');
      var fieldType = passwordField.attr('type');
  
      if (fieldType === 'password') {
        passwordField.attr('type', 'text');
        $(this).text('Hide');
      } else {
        passwordField.attr('type', 'password');
        $(this).text('Show');
      }
    });
  });
  