To build these apps, you will need to either be on a distribution with all the dependencies preinstalled such as Ubuntu GNOME or Fedora GNOME, or build every dependencies yourself.

Then install gnome builder (https://flathub.org/apps/org.gnome.Builder) and open the folder, it will ask to install dependencies you can then build it and run it.

**I put the project in the default location at /home/$USER/Projects/<projectDirectory>. Putting the project in another path may break the build.**

This project doesn't follow the GNOME HIG (https://developer.gnome.org/hig/) since it uses deprecated classes and doesn't follow other standards such as colors for example.

The main branch contains a prototype closer to what we need in term of UI. There is no way to insert files inside it for now (such as dictionaries) and there is 0 functioning logic plugged in.

The old branch actually contains some logic for a rock, paper, scissors. The main branch is a fork of the old branch and therefore there is some remnant of C code that are unused in main.

I inserted some screenshots inside the project folder itself.

# Warning ⚠️

It may not be wise to try to create a full application on libadwaita since it is a framework with a very heavy layer of abstraction built on top of libadwaita. It is therefore very difficult to actually understand what we are actually doing in libadwaita without knowing about GTK4 and Gobject.

Thus, actually doing the effort to learn GTK4 and building the project with that is going to be better for this particular work.