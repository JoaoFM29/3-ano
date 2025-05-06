$(function() {
    // Initialize counter
    var count = 0;
    
    // Display initial count
    $('.count').text(count);
    
    // Increment counter on '+' button click
    $('.increment-btn').click(function() {
      count++;
      $('.count').text(count);
    });
    
    // Decrement counter on '-' button click
    $('.decrement-btn').click(function() {
      if (count > 0) {
        count--;
        $('.count').text(count);
      }
    });
  });
  