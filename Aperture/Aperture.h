//
//  Aperture.h
//  Aperture
//
//  Created by Parker Moore on 6/19/11.
//  Copyright 2011 Linebreak. All rights reserved.
//

#import <AppKit/AppKit.h>
#import <ScriptingBridge/ScriptingBridge.h>


@class ApertureItem, ApertureApplication, ApertureColor, ApertureDocument, ApertureWindow, ApertureAttributeRun, ApertureCharacter, ApertureParagraph, ApertureText, ApertureAttachment, ApertureWord, ApertureAlbum, ApertureApplication, ApertureKeyword, AperturePhoto, AperturePrintSettings;

typedef enum {
	ApertureSavoAsk = 'ask ' /* Ask the user whether or not to save the file. */,
	ApertureSavoNo = 'no  ' /* Do not save the file. */,
	ApertureSavoYes = 'yes ' /* Save the file. */
} ApertureSavo;

typedef enum {
	ApertureViewEdit = 'edit' /* edit */,
	ApertureViewEvents = 'evts' /* events */,
	ApertureViewOrganize = 'orga' /* organize */
} ApertureView;

typedef enum {
	ApertureAlTyBookAlbum = 'book' /* book album */,
	ApertureAlTyEventsAlbum = 'eval' /* Album containing all the events in a library. */,
	ApertureAlTyFacesAlbum = 'faal' /* Album containing all the faces in a library. */,
	ApertureAlTyFlaggedAlbum = 'flal' /* Album containing all the flagged photos in a library. */,
	ApertureAlTyFolderAlbum = 'fldr' /* folder album */,
	ApertureAlTyLastImportAlbum = 'lstI' /* last import album */,
	ApertureAlTyLastMonthsAlbum = 'lstM' /* last months album */,
	ApertureAlTyLastRollsAlbum = 'lstR' /* last rolls album, but please use last import album now */,
	ApertureAlTyPhotoLibraryAlbum = 'aral' /* Album containing all the photos in a library. */,
	ApertureAlTyPlacesAlbum = 'plal' /* Album containing all the places in a library. */,
	ApertureAlTyPublishedAlbum = 'pubs' /* published album */,
	ApertureAlTyRegularAlbum = 'albm' /* regular album */,
	ApertureAlTySharedAlbum = 'papa' /* album of a shared library */,
	ApertureAlTySharedLibrary = 'papl' /* shared library; contains one or more children, which are shared albums */,
	ApertureAlTySlideshowAlbum = 'slds' /* slideshow album */,
	ApertureAlTySmartAlbum = 'smrt' /* smart album */,
	ApertureAlTySubscribedAlbum = 'subs' /* subscribed album */,
	ApertureAlTyTrashAlbum = 'tral' /* trash album */,
	ApertureAlTyUnknownAlbumType = 'aluk' /* unknown album type */
} ApertureAlTy;

typedef enum {
	ApertureEnumStandard = 'lwst' /* Standard PostScript error handling */,
	ApertureEnumDetailed = 'lwdt' /* print a detailed report of PostScript errors */
} ApertureEnum;



/*
 * Standard Suite
 */

// A scriptable object.
@interface ApertureItem : SBObject

@property (copy) NSDictionary *properties;  // All of the object's properties.

- (void) closeSaving:(ApertureSavo)saving savingIn:(NSURL *)savingIn;  // Close an object.
- (void) delete;  // Delete an object.
- (void) duplicateTo:(SBObject *)to withProperties:(NSDictionary *)withProperties;  // Copy object(s) and put the copies at a new location.
- (BOOL) exists;  // Verify if an object exists.
- (void) moveTo:(SBObject *)to;  // Move object(s) to a new location.
- (void) saveAs:(NSString *)as in:(NSURL *)in_;  // Save an object.
- (void) addTo:(id)to;  // Add the given object to the container.
- (void) assignKeywordString:(NSString *)string;  // Assign an existing keyword to the currently-selected photos.
- (void) autoImport;  // Start importing photos from the auto-import folder.
- (void) duplicateTo:(id)to;  // Create a duplicate of an object.
- (void) emptyTrash;  // Empty the Trash album.
- (void) importFrom:(NSString *)from forceCopy:(NSInteger)forceCopy to:(ApertureAlbum *)to;  // Import the given path.
- (ApertureAlbum *) newAlbumName:(NSString *)name;  // Create a new album.
- (void) nextSlide;  // Skip to previous slide in currently-playing slideshow.
- (void) pauseSlideshow;  // Pause the currently-playing slideshow.
- (void) previousSlide;  // Skip to next slide in currently-playing slideshow.
- (void) removeFrom:(id)from;  // Remove the given object from its container.
- (void) resumeSlideshow;  // Resume the currently-playing slideshow.
- (void) reverseGeocode;  // Call after setting a photo's latitude and longitude.  This command instructs Aperture to use lat/lon to look up the country, city, point of interest, etc.
- (void) select;  // Select one or more objects.
- (void) startSlideshowAsynchronous:(NSInteger)asynchronous displayIndex:(NSInteger)displayIndex iChat:(NSInteger)iChat usingAlbum:(NSString *)usingAlbum;  // Display a slideshow with the currently-selected photos or album.
- (void) stopSlideshow;  // End the currently-playing slideshow.

@end

// An application's top level scripting object.
@interface ApertureApplication : SBApplication

- (SBElementArray *) documents;
- (SBElementArray *) windows;

@property (readonly) BOOL frontmost;  // Is this the frontmost (active) application?
@property (copy, readonly) NSString *name;  // The name of the application.
@property (copy, readonly) NSString *version;  // The version of the application.

- (ApertureDocument *) open:(NSURL *)x;  // Open an object.
- (void) print:(NSURL *)x printDialog:(BOOL)printDialog withProperties:(AperturePrintSettings *)withProperties;  // Print an object.
- (void) quitSaving:(ApertureSavo)saving;  // Quit an application.

@end

// A color.
@interface ApertureColor : ApertureItem


@end

// A document.
@interface ApertureDocument : ApertureItem

@property (readonly) BOOL modified;  // Has the document been modified since the last save?
@property (copy) NSString *name;  // The document's name.
@property (copy) NSString *path;  // The document's path.


@end

// A window.
@interface ApertureWindow : ApertureItem

@property NSRect bounds;  // The bounding rectangle of the window.
@property (readonly) BOOL closeable;  // Whether the window has a close box.
@property (copy, readonly) ApertureDocument *document;  // The document whose contents are being displayed in the window.
@property (readonly) BOOL floating;  // Whether the window floats.
- (NSInteger) id;  // The unique identifier of the window.
@property NSInteger index;  // The index of the window, ordered front to back.
@property (readonly) BOOL miniaturizable;  // Whether the window can be miniaturized.
@property BOOL miniaturized;  // Whether the window is currently miniaturized.
@property (readonly) BOOL modal;  // Whether the window is the application's current modal window.
@property (copy) NSString *name;  // The full title of the window.
@property (readonly) BOOL resizable;  // Whether the window can be resized.
@property (readonly) BOOL titled;  // Whether the window has a title bar.
@property BOOL visible;  // Whether the window is currently visible.
@property (readonly) BOOL zoomable;  // Whether the window can be zoomed.
@property BOOL zoomed;  // Whether the window is currently zoomed.


@end



/*
 * Text Suite
 */

// This subdivides the text into chunks that all have the same attributes.
@interface ApertureAttributeRun : ApertureItem

- (SBElementArray *) attachments;
- (SBElementArray *) attributeRuns;
- (SBElementArray *) characters;
- (SBElementArray *) paragraphs;
- (SBElementArray *) words;

@property (copy) NSColor *color;  // The color of the first character.
@property (copy) NSString *font;  // The name of the font of the first character.
@property NSInteger size;  // The size in points of the first character.


@end

// This subdivides the text into characters.
@interface ApertureCharacter : ApertureItem

- (SBElementArray *) attachments;
- (SBElementArray *) attributeRuns;
- (SBElementArray *) characters;
- (SBElementArray *) paragraphs;
- (SBElementArray *) words;

@property (copy) NSColor *color;  // The color of the first character.
@property (copy) NSString *font;  // The name of the font of the first character.
@property NSInteger size;  // The size in points of the first character.


@end

// This subdivides the text into paragraphs.
@interface ApertureParagraph : ApertureItem

- (SBElementArray *) attachments;
- (SBElementArray *) attributeRuns;
- (SBElementArray *) characters;
- (SBElementArray *) paragraphs;
- (SBElementArray *) words;

@property (copy) NSColor *color;  // The color of the first character.
@property (copy) NSString *font;  // The name of the font of the first character.
@property NSInteger size;  // The size in points of the first character.


@end

// Rich (styled) text
@interface ApertureText : ApertureItem

- (SBElementArray *) attachments;
- (SBElementArray *) attributeRuns;
- (SBElementArray *) characters;
- (SBElementArray *) paragraphs;
- (SBElementArray *) words;

@property (copy) NSColor *color;  // The color of the first character.
@property (copy) NSString *font;  // The name of the font of the first character.
@property NSInteger size;  // The size in points of the first character.


@end

// Represents an inline text attachment.  This class is used mainly for make commands.
@interface ApertureAttachment : ApertureText

@property (copy) NSString *fileName;  // The path to the file for the attachment


@end

// This subdivides the text into words.
@interface ApertureWord : ApertureItem

- (SBElementArray *) attachments;
- (SBElementArray *) attributeRuns;
- (SBElementArray *) characters;
- (SBElementArray *) paragraphs;
- (SBElementArray *) words;

@property (copy) NSColor *color;  // The color of the first character.
@property (copy) NSString *font;  // The name of the font of the first character.
@property NSInteger size;  // The size in points of the first character.


@end



/*
 * Aperture suite
 */

// An album.  This abstract class represents the albums within an Aperture library.
@interface ApertureAlbum : ApertureItem

- (SBElementArray *) keywords;
- (SBElementArray *) photos;

@property (copy, readonly) NSArray *children;  // Array of album's children albums in the library hierarchy.
- (NSInteger) id;  // The unique ID of the album.
@property (copy) NSString *name;  // The name of the album.
@property (copy, readonly) ApertureAlbum *parent;  // Album's parent in the library hierarchy.
@property (readonly) ApertureAlTy type;  // Type of album.
@property (copy, readonly) NSString *url;  // URL of published/subscribed album.


@end

// Aperture's top level scripting object.
@interface ApertureApplication (ApertureSuite)

- (SBElementArray *) albums;
- (SBElementArray *) keywords;
- (SBElementArray *) photos;

@property (copy) ApertureAlbum *currentAlbum;  // The selected album.
@property (copy, readonly) ApertureAlbum *eventsAlbum;  // Events album.
@property (copy, readonly) ApertureAlbum *facesAlbum;  // Faces album.
@property (copy, readonly) ApertureAlbum *flaggedAlbum;  // Flagged photos album.
@property (readonly) NSInteger importing;  // Returns true if photo importing is in progress.
@property (copy, readonly) ApertureAlbum *lastImportAlbum;  // Last import album.
@property (copy, readonly) ApertureAlbum *lastMonthsAlbum;  // The set of N most recently imported month(s) of photos.  N is based on the preference set in Aperture.
@property (copy, readonly) ApertureAlbum *lastRollsAlbum;  // Now obsolete;  please use last import album.  Old: The set of N most recently imported roll(s) of photos.  N is based on the preference set in Aperture.
@property (copy, readonly) NSArray *localRootAlbums;  // Returns local albums that are at the root level in the source view.
@property (copy) NSString *mailAddress;  // The address for the e-mail.
@property (copy) NSString *mailRecipient;  // The recipient for the e-mail.
@property (copy) NSString *mailSubject;  // The subject for the e-mail.
@property (copy, readonly) ApertureAlbum *photoLibraryAlbum;  // The photo library.
@property (copy, readonly) ApertureAlbum *placesAlbum;  // Places album.
@property (copy) NSArray *selection;  // The current selection.
@property (copy, readonly) NSArray *sharedLibraryAlbums;  // Returns shared libraries from other computers on the network.
@property (readonly) NSInteger slideshowRunning;  // Returns true if a slideshow is currently running.
@property (copy, readonly) ApertureAlbum *trashAlbum;  // The set of deleted photos.
@property ApertureView view;  // The current view in the application.

@end

// A keyword to associate with a photo.
@interface ApertureKeyword : ApertureItem

@property (copy) NSString *name;  // The string value of the keyword.


@end

// A photo.
@interface AperturePhoto : ApertureItem

- (SBElementArray *) keywords;

@property NSInteger altitude;  // The GPS altitude in meters;  MAXFLOAT means no altitude information.
@property (copy) NSString *comment;  // A comment about the photo.
@property (copy) NSDate *date;  // The date of the photo.
@property (copy, readonly) NSArray *dimensions;  // The width and height of the photo in pixels.
@property (readonly) NSInteger height;  // The height of the photo in pixels.
- (NSInteger) id;  // The unique ID of the photo.
@property (copy, readonly) NSString *imageFilename;  // The name of the image file.
@property (copy, readonly) NSString *imagePath;  // The path to the image file.
@property NSInteger latitude;  // The GPS latitude in range -90.0 to 90.0;  MAXFLOAT means no GPS information.  Use reverse geocode command after setting lat/lon.
@property NSInteger longitude;  // The GPS longitude in range -180.0 to 180.0;  MAXFLOAT means no GPS information.  Measurement is taken from the prime meridian, so 'west' longitudes are negative numbers.  Use reverse geocode command after setting lat/lon.
@property (copy) NSString *name;  // The name (title) of the photo.
@property (copy, readonly) NSString *originalPath;  // The path to the original image as it was imported to Aperture.
@property NSInteger rating;  // The start rating (0 through 5).
@property (copy, readonly) NSString *thumbnailFilename;  // The name of the thumbnail file.
@property (copy, readonly) NSString *thumbnailPath;  // The path to the thumbnail file.
@property (copy) NSString *title;  // The title (name) of the photo.
@property (readonly) NSInteger width;  // The width of the photo in pixels.


@end



/*
 * Type Definitions
 */

@interface AperturePrintSettings : SBObject

@property NSInteger copies;  // the number of copies of a document to be printed
@property BOOL collating;  // Should printed copies be collated?
@property NSInteger startingPage;  // the first page of the document to be printed
@property NSInteger endingPage;  // the last page of the document to be printed
@property NSInteger pagesAcross;  // number of logical pages laid across a physical page
@property NSInteger pagesDown;  // number of logical pages laid out down a physical page
@property (copy) NSDate *requestedPrintTime;  // the time at which the desktop printer should print the document
@property ApertureEnum errorHandling;  // how errors are handled
@property (copy) NSString *faxNumber;  // for fax number
@property (copy) NSString *targetPrinter;  // for target printer

- (void) closeSaving:(ApertureSavo)saving savingIn:(NSURL *)savingIn;  // Close an object.
- (void) delete;  // Delete an object.
- (void) duplicateTo:(SBObject *)to withProperties:(NSDictionary *)withProperties;  // Copy object(s) and put the copies at a new location.
- (BOOL) exists;  // Verify if an object exists.
- (void) moveTo:(SBObject *)to;  // Move object(s) to a new location.
- (void) saveAs:(NSString *)as in:(NSURL *)in_;  // Save an object.
- (void) addTo:(id)to;  // Add the given object to the container.
- (void) assignKeywordString:(NSString *)string;  // Assign an existing keyword to the currently-selected photos.
- (void) autoImport;  // Start importing photos from the auto-import folder.
- (void) duplicateTo:(id)to;  // Create a duplicate of an object.
- (void) emptyTrash;  // Empty the Trash album.
- (void) importFrom:(NSString *)from forceCopy:(NSInteger)forceCopy to:(ApertureAlbum *)to;  // Import the given path.
- (ApertureAlbum *) newAlbumName:(NSString *)name;  // Create a new album.
- (void) nextSlide;  // Skip to previous slide in currently-playing slideshow.
- (void) pauseSlideshow;  // Pause the currently-playing slideshow.
- (void) previousSlide;  // Skip to next slide in currently-playing slideshow.
- (void) removeFrom:(id)from;  // Remove the given object from its container.
- (void) resumeSlideshow;  // Resume the currently-playing slideshow.
- (void) reverseGeocode;  // Call after setting a photo's latitude and longitude.  This command instructs Aperture to use lat/lon to look up the country, city, point of interest, etc.
- (void) select;  // Select one or more objects.
- (void) startSlideshowAsynchronous:(NSInteger)asynchronous displayIndex:(NSInteger)displayIndex iChat:(NSInteger)iChat usingAlbum:(NSString *)usingAlbum;  // Display a slideshow with the currently-selected photos or album.
- (void) stopSlideshow;  // End the currently-playing slideshow.

@end
