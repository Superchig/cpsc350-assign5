- Student and Faculty should have a method that prints all their info, which
  will be useful for multiple user commands

- Rollback class w/ Stack
  - Transaction class, Stack holds Transaction objects
  - Member variables that keep track of what was done (insert/delete), another
    of the data (what was inserted/deleted)
  - Whenever insert is done, store a delete
  - Whenever a delete is done, store an insert
