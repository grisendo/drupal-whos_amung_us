(function ($) {

  Drupal.behaviors.whosAmungUsColorPicker = {
    attach: function (context, settings) {
      $('.wau-has-color-picker:not(.color-processed)', context).each(
        function () {
          var $this = $(this);
          var $id = $this.attr('id') + '-color-placeholder';
          $this.addClass('color-processed');
          $this.parent().append('<div id="' + $id + '"></div>');
          $this.myfarb = $.farbtastic('#' + $id);
          $this.myfarb.linkTo(
            function (color) {
              $this.val(color.replace('#', '').toLowerCase());
            }
          );
          $this.myfarb.setColor('#' + $this.val());
        }
      );
    }
  };

})(jQuery);
