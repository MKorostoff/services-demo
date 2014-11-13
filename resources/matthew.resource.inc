<?php

function _matthew_dashboard() {
  $reponse = array();
  $serviceController = new ServicesEntityResourceControllerClean();





  //Create the about section;
  $about = $serviceController->retrieve('node', '225', 'body,title,changed', '225');
  if (!empty($about)) {
    $about['body'] = strip_tags($about['body']['value']);
    $about['body'] = substr($about['body'], 0, 120) . '...';
    $response['about'] = $about;
  }






  //Build the who's new section
  $entityController = new EntityFieldQuery();
  $new_users = $entityController->entityCondition('entity_type', 'user')
      ->propertyOrderBy('created', 'DESC')
      ->range(0, 5)
      ->execute();

  $new_users = array_keys($new_users['user']);
  foreach ($new_users as $u) {
    $user[] = $serviceController->retrieve('user', strval($u), 'name,created', NULL);
  }
  $response['users'] = $user;






  //build the affiliate links section
  $affliate_links = nodequeue_load_nodes(1);
  foreach ($affliate_links as $n) {
    $links[] = $n->field_link['und'][0]['value'];
  }
  $response['links'] = $links;





  //Build the 'hot right now' section
  $entityController = new EntityFieldQuery();
  $top_three_articles = $entityController->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'article')
    ->fieldCondition('field_tags', 'tid', 1)
    ->range(0, 3)
    ->execute();

  $top_three_articles = array_keys($top_three_articles['node']);
  foreach ($top_three_articles as $n) {
    $article = $serviceController->retrieve('node', strval($n), 'title,author,created,image', strval($n));
    $article['image'] = file_create_url(file_load($article['image']['file']['id'])->uri);
    $article['author'] = user_load($article['author']['id'])->name;
    $articles[] = $article;
  }
  $response['hot_right_now'] = $articles;






  return $response;
}
