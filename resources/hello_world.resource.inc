<?php

function _matthew_hello_world($name) {

  // return "hello world";
  $name = (!empty($name)) ? check_plain($name) : 'world';

  return array(
    "hello" => $name,
    "goodbye" => "forever",
    "php_cms" => array(
      "wordpress",
      "joomla",
      "drupal",
    )
  );

}
