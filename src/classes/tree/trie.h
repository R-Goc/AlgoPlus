#ifndef TRIE_H
#define TRIE_H

#ifdef __cplusplus
#include <iostream>
#endif

/*
 *trie class
 */
class trie {
private:
  struct node {
    std::shared_ptr<node> characters[26]{nullptr};
    bool end_word{false};
  };

  std::shared_ptr<node> root;

public:
  explicit trie(std::vector<std::string> v = {}) noexcept
      : root(std::make_shared<node>()) {
    if (!v.empty()) {
      for (auto &x : v) {
        this->insert(x);
      }
    }
  }

  /*
   *empty function.
   *returns true if the trie is empty.
   */
  bool empty() { return root == nullptr; }
  /*
   *insert function.
   *@param key: the key to be inserted.
   */
  void insert(std::string key);

  /*
   *remove function.
   *@param key: the key to be removed.
   */
  void remove(std::string key);
  /*
   *search function.
   *@param key: the key to be searched.
   *returns true if the word exist in the tree.
   */
  bool search(std::string key);

  friend std::ostream &operator<<(std::ostream &out, trie &t);

private:
  /*
   *__children function.
   *checks if a node has children or not.
   */
  bool __children(std::shared_ptr<node> root) {
    for (int64_t i = 0; i < 26; i++) {
      if (root->characters[i]) {
        return true;
      }
    }
    return false;
  }
  /*
   *__remove function.
   *helper function of remove().
   */
  std::shared_ptr<node> __remove(std::shared_ptr<node> current,
                                 std::string word, int64_t index) {
    if (word.size() == index) {
      if (current->end_word) {
        current->end_word = false;
      }
      if (__children(current)) {
        return current;
      }
      return nullptr;
    }

    int64_t i = word[index] - 'a';
    if (!current->characters[i]) {
      return nullptr;
    }
    current->characters[i] = __remove(current->characters[i], word, index + 1);
    if (current->characters[i] || __children(current)) {
      return current;
    }
    return nullptr;
  }
};

void trie::insert(std::string key) {
  std::shared_ptr<node> current = root;
  for (auto &c : key) {
    int64_t index = c - 'a';
    if (!current->characters[index]) {
      current->characters[index] = std::make_shared<node>();
    }
    current = current->characters[index];
  }
  current->end_word = true;
}

void trie::remove(std::string key) { root = __remove(root, key, 0); }

bool trie::search(std::string key) {
  std::shared_ptr<node> current = root;
  for (auto &c : key) {
    int64_t index = c - 'a';
    if (!current->characters[index]) {
      return false;
    }
    current = current->characters[index];
  }
  return current->end_word;
}

#endif