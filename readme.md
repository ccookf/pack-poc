# Pack/Unpack proof of concept

In short I wanted a basic setup to be able to hide and unhide application resources at runtime. The next step from here would be allowing the system to pack multiple files at once. Ideally the final iteration of this project will be a library that will allow for bundling multiple resources into a single encrypted data file. However, having a single file packed with basic encryption is enough to get the point accross for now.

### Encryption

The encryption used was a basic XOR operation on each character. The key used for this is stored in the header of the packed files so that any application that knows how to read the file can decrypt it. I chose to include the key like this as the primary purpose of this test wasn't to make resources secure so much as to prove they can be hidden from the end user.

### Why not use a standard resource packer?

This solution is both simple, cross-platform, and annoying to anyone who will fiddle with it. Just by virtue of being a custom system it is already beyond the means of the average user to break, so I am more than satisfied with its expected performance.
