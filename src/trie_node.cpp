#include <vector>
#include <string>
#include <map>

#include "../include/trie.h"

trie_node::trie_node(std::string word) : children() {
  insert(word);
}

trie_node::trie_node(const trie_node& copy) {
  isEntry = copy.isEntry;
  for (const auto& subNode: copy.children) {
    children[subNode.first] = std::unique_ptr<trie_node>(new trie_node(*subNode.second));
  }
}

trie_node& trie_node::operator=(trie_node rhs) {
  isEntry = rhs.isEntry;
  for (const auto& subNode: rhs.children) {
    children[subNode.first] = std::unique_ptr<trie_node>(new trie_node(*subNode.second));
  }
  return *this;
}

bool trie_node::find(std::string word) {
  if (word == "")
    return isEntry;

  char        head = word[0];
  std::string tail = getTail(word);
  if (children.find(head) != children.end())
    return children[head]->find(tail);

  return false;
}

bool trie_node::has_prefix(std::string prefix) {
  if (prefix == "")
    return true;

  char        head = prefix[0];
  std::string tail = getTail(prefix);
  if (children.find(head) != children.end())
    return children[head]->has_prefix(tail);

  return false;
}

void trie_node::insert(std::string word) {
  if (word == "")
    isEntry = true;
  else {
    char        head = word[0];
    std::string tail = getTail(word);

    if (children.find(head) == children.end())
      children[head] = std::unique_ptr<trie_node>(new trie_node(tail));
    else
      children[head]->insert(tail);
  }
}

std::string trie_node::getTail(std::string word) {
  std::string output = "";
  if (word.length() > 0)
    output = word.substr(1, word.length() - 1);
  return output;
}