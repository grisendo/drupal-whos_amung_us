<?php

/**
 * Area handler for Follow link.
 *
 * @ingroup views_area_handlers
 */
class views_handler_area_whos_amung_us extends views_handler_area {

  /**
   * Init the handler with necessary data.
   *
   * @param stdClass $view
   *   The $view object this handler is attached to.
   * @param array $options
   *   The item from the database; the actual contents of this will vary
   *   based upon the type of handler.
   */
  public function init(&$view, &$options) {
    parent::init($view, $options);
    if ($this->handler_type == 'empty') {
      $this->options['empty'] = TRUE;
    }
  }

  /**
   * Get this field's label.
   */
  public function label() {
    if (!isset($this->options['label'])) {
      return $this->ui_name();
    }
    return $this->options['label'];
  }

  /**
   * Information about options for all kinds of purposes will be held here.
   * @code
   * 'option_name' => array(
   *  - 'default' => default value,
   *  - 'translatable' => (optional) TRUE/FALSE (wrap in t() on export if true),
   *  - 'contains' => (optional) array of items this contains, with its own
   *      defaults, etc. If contains is set, the default will be ignored and
   *      assumed to be array().
   *  - 'bool' => (optional) TRUE/FALSE Is the value a boolean value. This will
   *      change the export format to TRUE/FALSE instead of 1/0.
   *  - 'export' => (optional) FALSE or a callback for special export handling
   *      if necessary.
   *  - 'unpack_translatable' => (optional) callback for special handling for
   *      translating data within the option, if necessary.
   *  ),
   *
   * @return array
   *   Returns the options of this handler/plugin.
   */
  public function option_definition() {
    $options = parent::option_definition();
    $this->definition['field'] = !empty($this->definition['field']) ? $this->definition['field'] : '';
    $label = !empty($this->definition['label']) ? $this->definition['label'] : $this->definition['field'];
    $options['label'] = array('default' => $label, 'translatable' => TRUE);
    $options['text'] = array('default' => 'Follow', 'translatable' => TRUE);
    return $options;
  }

  /**
   * Provide text for the administrative summary.
   */
  public function admin_summary() {
    return $this->label();
  }

  /**
   * Build the options form.
   */
  public function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['label'] = array(
      '#type' => 'textfield',
      '#title' => t('Label'),
      '#default_value' => isset($this->options['label']) ? $this->options['label'] : '',
      '#description' => t('The label for this area that will be displayed only administratively.'),
    );
    $form['text'] = array(
      '#type' => 'textfield',
      '#title' => t('Text'),
      '#default_value' => isset($this->options['text']) ? $this->options['text'] : 'Follow',
    );
  }

  /**
   * Called to add the field to a query.
   */
  public function query() {
    return NULL;
  }

  /**
   * Render the field.
   *
   * @param stdClass $empty
   *   The values retrieved from the database.
   */
  public function render($empty = FALSE) {
    if (!$empty) {
      $params = $_GET;
      unset($params['q']);
      $params5 = $params;
      $params5['items_per_page'] = 5;
      $params10 = $params;
      $params10['items_per_page'] = 10;
      $params20 = $params;
      $params20['items_per_page'] = 20;
      if (isset($_GET['items_per_page'])) {
        if ($_GET['items_per_page'] == 5) {
          $attr5 = array('class' => array('pager-current'));
          $attr10 = array();
          $attr20 = array();
        }
        elseif ($_GET['items_per_page'] == 10) {
          $attr5 = array();
          $attr10 = array('class' => array('pager-current'));
          $attr20 = array();
        }
        elseif ($_GET['items_per_page'] == 20) {
          $attr5 = array();
          $attr10 = array();
          $attr20 = array('class' => array('pager-current'));
        }
        else {
          $attr5 = array('class' => array('pager-current'));
          $attr10 = array();
          $attr20 = array();
        }
      }
      else {
        $attr5 = array('class' => array('pager-current'));
        $attr10 = array();
        $attr20 = array();
      }
      return
        '<div class="items-per-page-links">' .
        t('Items per page') .
        ': ' .
        implode(
          ' ',
          array(
            l(5, $_GET['q'], array('query' => $params5, 'attributes' => $attr5)),
            l(10, $_GET['q'], array('query' => $params10, 'attributes' => $attr10)),
            l(20, $_GET['q'], array('query' => $params20, 'attributes' => $attr20)),
          )
        ) .
        '</div>'
      ;
    }
    return '';
  }

  /**
   * Provides the handler some groupby.
   */
  public function use_group_by() {
    return FALSE;
  }

}
